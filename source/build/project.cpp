#include "project.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "publish.hpp"

namespace iris {

    Project::Project(JSContext* context)
        : m_context(context)
    {
    }

    Project::~Project()
    {
    }

    bool Project::load(const std::string& filePath)
    {
        // Validate project type

        static const char* Extension = ".xfl";
        static const size_t ExtensionLength = strlen(Extension);

        if (filePath.length() < ExtensionLength ||
            filePath.compare(filePath.length() - ExtensionLength, ExtensionLength, Extension) != 0)
        {
            return false;
        }

        // Create intermediate directory

        m_projectPath = filePath;
        const size_t last_slash = m_projectPath.find_last_of('\\');
        if (last_slash != std::string::npos)
        {
            m_projectPath.erase(last_slash, m_projectPath.length() - last_slash);
        }

        m_intermediatePath = m_projectPath + "\\intermediate";

        helpers::createDirectory(m_intermediatePath);

        // Set up logging

        m_logger = std::shared_ptr<Logger>(new Logger(m_intermediatePath + "\\output.log"));
        m_logger->write("Opening log.");

        // Load project settings

        m_publish = std::shared_ptr<Publish>(new Publish(*this, m_logger));
        if (!m_publish->load(m_projectPath + "\\PublishSettings.xml"))
        {
            return false;
        }

        return true;
    }

};