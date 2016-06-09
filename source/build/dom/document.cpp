#include "document.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"
#include "../project.hpp"
#include "bitmapitem.hpp"

namespace iris {
namespace dom {

    Document::Document(Project& project)
        : m_project(project)
    {
    }

    Document::~Document()
    {
    }

    bool Document::load(const std::string& filePath)
    {
        Logger::get().write("Loading \"%s\".", filePath.c_str());
        if (!helpers::fileExists(filePath))
        {
            Logger::get().write("ERROR! Failed to load file.");

            return false;
        }

        m_document = std::shared_ptr<TiXmlDocument>(new TiXmlDocument());
        if (!m_document->LoadFile(filePath.c_str()) ||
            m_document->RootElement() == nullptr)
        {
            Logger::get().write("ERROR! Failed to parse document as XML.");

            return false;
        }

        TiXmlElement* media = m_document->RootElement()->FirstChildElement("media");
        if (media != nullptr &&
            !parseMedia(media))
        {
            return false;
        }

        return true;
    }

    bool Document::parseMedia(TiXmlElement* element)
    {
        TiXmlElement* bitmap_element = element->FirstChildElement("DOMBitmapItem");
        while (bitmap_element != nullptr)
        {
            std::shared_ptr<BitmapItem> bitmap(new BitmapItem(*this));

            if (!bitmap->parse(bitmap_element))
            {
                Logger::get().write("ERROR! Failed to parse bitmap item.");

                return false;
            }

            m_bitmaps.push_back(bitmap);

            bitmap_element = bitmap_element->NextSiblingElement("DOMBitmapItem");
        }

        return true;
    }

};
};