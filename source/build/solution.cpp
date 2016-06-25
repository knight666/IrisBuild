/*
    Copyright (c) 2016 Bigpoint GmbH

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "solution.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "dependencygraph.hpp"
#include "project.hpp"
#include "visitor.hpp"

namespace iris {

    Solution::Solution()
    {
    }

    Solution::~Solution()
    {
    }

    std::shared_ptr<Project> Solution::addProject(const std::string& filePath)
    {
        std::map<std::string, std::shared_ptr<Project>>::iterator found = m_projects.find(filePath);
        if (found != m_projects.end())
        {
            return found->second;
        }

        std::shared_ptr<Project> project(new Project(*this));
        if (!project->parse(filePath))
        {
            return nullptr;
        }

        m_projects.insert(std::make_pair(project->getFilePath(), project));

        save(m_filePath);

        return project;
    }

    bool Solution::removeProject(const std::string& filePath)
    {
        std::map<std::string, std::shared_ptr<Project>>::iterator found = m_projects.find(filePath);
        if (found != m_projects.end())
        {
            IRIS_LOG_ERROR("Project \"%s\" is not registered or has already been removed.", filePath.c_str());

            return false;
        }

        m_projects.erase(found);

        save(m_filePath);

        return true;
    }

    bool Solution::verify()
    {
        bool result = true;

        for (std::pair<std::string, std::shared_ptr<Project>> project : m_projects)
        {
            project.second->reset();
        }

        for (std::pair<std::string, std::shared_ptr<Project>> project : m_projects)
        {
            result = result && project.second->check();
        }

        return result;
    }

    bool Solution::build(JSObject* context)
    {
        bool result = true;

        // Clear result cache

        for (std::pair<std::string, std::shared_ptr<Project>> project : m_projects)
        {
            project.second->reset();
        }

        // Build dependency graph

        DependencyGraph graph;

        for (std::pair<std::string, std::shared_ptr<Project>> project : m_projects)
        {
            project.second->update(graph);
        }

        std::vector<DependencyGraph::Dependency> dependencies = graph.getFlattenedList();

        // Build tasks

        for (DependencyGraph::Dependency& dependency : dependencies)
        {
            if (!dependency.task->build(context))
            {
                result = false;

                break;
            }
        }

        IRIS_LOG_TRACE("build result %s", (result ? "succeeded" : "failed"));

        return result;
    }

    bool Solution::accept(Visitor& visitor)
    {
        bool result = visitor.visitEnter(*this);

        for (std::pair<std::string, std::shared_ptr<Project>> project : m_projects)
        {
            if (!project.second->accept(visitor))
            {
                return false;
            }
        }

        result = result && visitor.visitLeave(*this);

        return result;
    }

    bool Solution::load(const std::string& filePath)
    {
        IRIS_LOG_INFO("Loading solution \"%s\".", filePath.c_str());

        if (!helpers::fileExists(filePath))
        {
            IRIS_LOG_ERROR("Failed to load solution at \"%s\".", filePath.c_str());

            return false;
        }

        TiXmlDocument document;
        if (!document.LoadFile(filePath.c_str()) ||
            document.RootElement() == nullptr)
        {
            IRIS_LOG_ERROR("Failed to parse document as XML.");

            return false;
        }

        // Delete previous projects

        m_projects.clear();

        // Parse version

        std::string version_text = helpers::readAttributeText(document.RootElement(), "version");

        uint32_t version = 0;
        sscanf_s(version_text.c_str(), "%d", &version);

        IRIS_LOG_TRACE("version: \"%s\".", version_text.c_str());

        if (version > IRIS_SAVE_VERSION)
        {
            IRIS_LOG_ERROR("Unsupported solution version \"%s\".", version_text.c_str());

            return false;
        }

        // Extract working directory from path

        char drive[_MAX_DRIVE] = { 0 };
        char directory[_MAX_DIR] = { 0 };
        _splitpath(filePath.c_str(), drive, directory, nullptr, nullptr);

        m_workingDirectory = std::string(drive) + directory;

        IRIS_LOG_TRACE("workingDirectory: \"%s\".", m_workingDirectory.c_str());

        // Load projects

        TiXmlElement* projects = document.RootElement()->FirstChildElement("Projects");
        if (projects == nullptr)
        {
            IRIS_LOG_ERROR("Missing top-level \"Projects\" element.");

            return false;
        }

        XML_FOR_EACH(projects, "Project", project_element)
        {
            std::shared_ptr<Project> project(new Project(*this));

            if (!project->load(project_element, version))
            {
                IRIS_LOG_ERROR("Failed to project item.");

                return false;
            }

            m_projects.insert(std::make_pair(project->getFilePath(), project));
        }

        m_filePath = filePath;

        return true;
    }

    bool Solution::save(const std::string& path)
    {
        TiXmlDocument document;

        TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "utf-8", "");
        document.LinkEndChild(declaration);

        TiXmlElement* root_element = new TiXmlElement("Solution");
        root_element->SetAttribute("version", IRIS_SAVE_VERSION);
        document.LinkEndChild(root_element);

        TiXmlElement* projects_element = new TiXmlElement("Projects");
        root_element->LinkEndChild(projects_element);

        for (std::pair<std::string, std::shared_ptr<Project>> project : m_projects)
        {
            if (!project.second->save(projects_element, IRIS_SAVE_VERSION))
            {
                return false;
            }
        }

        return document.SaveFile(path.c_str());
    }

};