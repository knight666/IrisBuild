#include "publish.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "project.hpp"
#include "visitor.hpp"

namespace iris {

    Publish::Publish(Project& project)
        : m_project(project)
        , m_enabled(false)
    {
    }

    Publish::~Publish()
    {
    }

    bool Publish::accept(Visitor& visitor)
    {
        return visitor.visitEnter(*this) && visitor.visitLeave(*this);
    }

    bool Publish::load(const std::string& filePath)
    {
        IRIS_LOG_TRACE("Loading \"%s\".", filePath.c_str());

        if (!helpers::fileExists(filePath))
        {
            IRIS_LOG_ERROR("Failed to load file.");

            return false;
        }

        m_document = std::shared_ptr<TiXmlDocument>(new TiXmlDocument());
        if (!m_document->LoadFile(filePath.c_str()) ||
            m_document->RootElement() == nullptr)
        {
            IRIS_LOG_ERROR("Failed to parse document as XML.");

            return false;
        }

        TiXmlElement* profile = m_document->RootElement()->FirstChildElement("flash_profile");
        if (profile == nullptr)
        {
            IRIS_LOG_ERROR("Missing \"flash_profile\" element in hierarchy.");

            return false;
        }

        // Parse publish properties

        TiXmlElement* publish_format = profile->FirstChildElement("PublishFormatProperties");
        if (publish_format == nullptr)
        {
            IRIS_LOG_ERROR("Missing \"PublishFormatProperties\" element under \"flash_profile\".");

            return false;
        }

        m_enabled = std::string(publish_format->Attribute("enabled")) == "true";
        IRIS_LOG_INSANE("\tenabled: %s", m_enabled ? "yes" : "no");

        m_publishPath = helpers::readElementText(publish_format, "flashFileName");
        if (m_publishPath.empty())
        {
            return false;
        }

        m_publishPath = helpers::absolutePath(m_project.getProjectPath() + "\\..\\" + m_publishPath);
        IRIS_LOG_INSANE("\tpublishPath: %s", m_publishPath.c_str());

        // Parse flash properties

        TiXmlElement* publish_flash = profile->FirstChildElement("PublishFlashProperties");
        if (publish_flash == nullptr)
        {
            IRIS_LOG_ERROR("Missing \"PublishFlashProperties\" element under \"flash_profile\".");

            return false;
        }

        m_actionScriptVersion = helpers::readElementText(publish_flash, "ActionScriptVersion");
        IRIS_LOG_INSANE("\tactionScriptVersion: %s", m_actionScriptVersion.c_str());

        if (m_actionScriptVersion == "3")
        {
            m_packagePaths = helpers::readElementText(publish_flash, "AS3PackagePaths");
            m_constants = helpers::readElementText(publish_flash, "AS3ConfigConst");
        }
        else
        {
            m_packagePaths = helpers::readElementText(publish_flash, "PackagePaths");
            m_constants = "";
        }

        IRIS_LOG_INSANE("\tpackagePaths: %s", m_packagePaths.c_str());
        IRIS_LOG_INSANE("\tconstants: %s", m_constants.c_str());

        m_documentClass = helpers::readElementText(publish_flash, "DocumentClass");
        IRIS_LOG_INSANE("\tdocumentClass: %s", m_documentClass.c_str());

        return true;
    }

};