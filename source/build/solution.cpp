#include "solution.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "project.hpp"

namespace iris {

    Solution* Solution::s_instance = nullptr;

    Solution::Solution()
    {
    }

    Solution::~Solution()
    {
    }

    Solution& Solution::get()
    {
        return *s_instance;
    }

    void Solution::create()
    {
        s_instance = new Solution();
    }

    void Solution::destroy()
    {
        delete s_instance;
        s_instance = nullptr;
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

        // Parse version

        std::string version_text = helpers::readAttributeText(document.RootElement(), "version");

        int32_t version_semantic[3] = { 0 };
        sscanf_s(version_text.c_str(), "%d.%d.%d", &version_semantic[0], &version_semantic[1], &version_semantic[2]);
        uint32_t version = IRIS_SAVE_VERSION_MAKE(version_semantic[0], version_semantic[1], version_semantic[2]);

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
            std::shared_ptr<Project> project(new Project(nullptr));

            if (!project->load(project_element, version))
            {
                IRIS_LOG_ERROR("Failed to project item.");

                return false;
            }

            m_projects.push_back(project);
        }

        return true;
    }

    void Solution::save(const std::string& path)
    {

    }

};