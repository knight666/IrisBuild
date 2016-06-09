#include "publish.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"

namespace iris {

    Publish::Publish(std::shared_ptr<Logger> logger)
        : m_logger(logger)
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

        TiXmlNode* profile = root->FirstChild("flash_profile");
        if (profile == nullptr)
        {
            m_logger->write("ERROR! Missing \"flash_profile\" element in hierarchy.");

            return false;
        }

        TiXmlElement* publish_format = nullptr;
        if (!findElement(profile, "PublishFormatProperties", &publish_format))
        {
            return false;
        }

        const char* enabled = publish_format->Attribute("enabled");
        m_logger->write("enabled: %s", enabled);

        return true;
    }

    bool Publish::findElement(TiXmlNode* parent, const char* name, TiXmlElement** target)
    {
        TiXmlNode* node = parent->FirstChildElement(name);
        if (node != nullptr)
        {
            *target = node->ToElement();
        }

        if (node == nullptr ||
            *target == nullptr)
        {
            m_logger->write("ERROR! Missing \"%s\" element in hierarchy.", name);

            return false;
        }

        return true;
    }

};