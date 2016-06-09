#include "publish.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "project.hpp"

namespace iris {

    Publish::Publish(Project& project, std::shared_ptr<Logger> logger)
        : m_project(project)
        , m_logger(logger)
        , m_enabled(false)
    {
    }

    Publish::~Publish()
    {
    }

    bool Publish::load(const std::string& filePath)
    {
        m_logger->write("Loading publish settings at \"%s\".", filePath.c_str());
        if (!helpers::fileExists(filePath))
        {
            m_logger->write("ERROR! Failed to load file.");

            return false;
        }

        m_document = std::shared_ptr<TiXmlDocument>(new TiXmlDocument());
        if (!m_document->LoadFile(filePath.c_str()) ||
            m_document->RootElement() == nullptr)
        {
            m_logger->write("ERROR! Failed to parse document as XML.");

            return false;
        }

        TiXmlElement* profile = m_document->RootElement()->FirstChildElement("flash_profile");
        if (profile == nullptr)
        {
            m_logger->write("ERROR! Missing \"flash_profile\" element in hierarchy.");

            return false;
        }

        // Parse publish properties

        TiXmlElement* publish_format = profile->FirstChildElement("PublishFormatProperties");
        if (publish_format == nullptr)
        {
            m_logger->write("ERROR! Missing \"PublishFormatProperties\" element under \"flash_profile\".");

            return false;
        }

        m_enabled = std::string(publish_format->Attribute("enabled")) == "true";
        m_logger->write("\tenabled: %s", m_enabled ? "yes" : "no");

        m_publishPath = helpers::readElementText(m_logger, publish_format, "flashFileName");
        if (m_publishPath.empty())
        {
            return false;
        }

        m_publishPath = helpers::absolutePath(m_project.getProjectPath() + "\\..\\" + m_publishPath);
        m_logger->write("\tpublishPath: %s", m_publishPath.c_str());

        // Parse flash properties

        TiXmlElement* publish_flash = profile->FirstChildElement("PublishFlashProperties");
        if (publish_flash == nullptr)
        {
            m_logger->write("ERROR! Missing \"PublishFlashProperties\" element under \"flash_profile\".");

            return false;
        }

        m_actionScriptVersion = helpers::readElementText(m_logger, publish_flash, "ActionScriptVersion");
        m_logger->write("\tactionScriptVersion: %s", m_actionScriptVersion.c_str());

        if (m_actionScriptVersion == "3")
        {
            m_packagePaths = helpers::readElementText(m_logger, publish_flash, "AS3PackagePaths");
            m_constants = helpers::readElementText(m_logger, publish_flash, "AS3ConfigConst");
        }
        else
        {
            m_packagePaths = helpers::readElementText(m_logger, publish_flash, "PackagePaths");
            m_constants = "";
        }

        m_logger->write("\tpackagePaths: %s", m_packagePaths.c_str());
        m_logger->write("\tconstants: %s", m_constants.c_str());

        m_documentClass = helpers::readElementText(m_logger, publish_flash, "DocumentClass");
        m_logger->write("\tdocumentClass: %s", m_documentClass.c_str());

        return true;
    }

};