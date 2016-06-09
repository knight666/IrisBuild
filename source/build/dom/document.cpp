#include "document.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"
#include "../project.hpp"

namespace iris {
namespace dom {

    Document::Document(Project& project, std::shared_ptr<Logger> logger)
        : m_project(project)
        , m_logger(logger)
    {
    }

    Document::~Document()
    {
    }

    bool Document::load(const std::string& filePath)
    {
        m_logger->write("Loading \"%s\".", filePath.c_str());
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

        TiXmlElement* media = m_document->RootElement()->FirstChildElement("media");
        if (media != nullptr &&
            !parseMedia(*media))
        {
            return false;
        }

        return true;
    }

    bool Document::parseMedia(TiXmlElement& element)
    {
        m_logger->write("media found");

        return true;
    }

};
};