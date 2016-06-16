#include "solution.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "project.hpp"
#include "visitor.hpp"

namespace iris {

    Solution::Solution()
    {
    }

    Solution::~Solution()
    {
    }

    std::shared_ptr<Project> Solution::getCurrentProject() const
    {
        if (m_projects.size() == 0)
        {
            return nullptr;
        }

        return m_projects[m_projects.size() - 1];
    }

    void Solution::addProject(std::shared_ptr<Project> project)
    {
        m_projects.push_back(project);
    }

    bool Solution::verify()
    {
        bool result = true;

        for (std::shared_ptr<Project> project : m_projects)
        {
            project->reset();
        }

        for (std::shared_ptr<Project> project : m_projects)
        {
            result = result && project->check();
        }

        return result;
    }

    bool Solution::accept(Visitor& visitor)
    {
        bool result = visitor.visitEnter(*this);

        for (std::shared_ptr<Project> project : m_projects)
        {
            if (!project->accept(visitor))
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

            m_projects.push_back(project);
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

        for (std::shared_ptr<Project> project : m_projects)
        {
            if (!project->save(projects_element, IRIS_SAVE_VERSION))
            {
                return false;
            }
        }

        return document.SaveFile(path.c_str());
    }

};