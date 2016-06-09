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
        if (!m_document->LoadFile(filePath.c_str()))
        {
            m_logger->write("ERROR! Failed to parse document as XML.");

            return false;
        }

        TiXmlElement* root = m_document->RootElement();

        TiXmlElement* profile = root->FirstChildElement("flash_profile");
        if (profile == nullptr)
        {
            m_logger->write("ERROR! Missing \"flash_profile\" element in hierarchy.");

            return false;
        }

        TiXmlElement* publish_format = profile->FirstChildElement("PublishFormatProperties");
        if (publish_format == nullptr)
        {
            m_logger->write("ERROR! Missing \"PublishFormatProperties\" element under \"flash_profile\".");

            return false;
        }

        m_enabled = std::string(publish_format->Attribute("enabled")) == "true";
        m_logger->write("\tenabled: %s", m_enabled ? "yes" : "no");

        TiXmlElement* flash_file_name = publish_format->FirstChildElement("flashFileName");
        if (flash_file_name == nullptr)
        {
            m_logger->write("ERROR! Missing \"flashFileName\" element under \"PublishFormatProperties\".");

            return false;
        }

        m_publishPath = helpers::absolutePath(m_project.getProjectPath() + "\\..\\" + flash_file_name->GetText());
        m_logger->write("\tpublishPath: %s", m_publishPath.c_str());

        return true;
    }

};