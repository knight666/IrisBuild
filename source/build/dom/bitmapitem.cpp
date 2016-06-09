#include "bitmapitem.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"

namespace iris {
namespace dom {

    BitmapItem::BitmapItem(Document& document)
        : m_document(document)
        , m_element(nullptr)
    {
    }

    BitmapItem::~BitmapItem()
    {
    }

    bool BitmapItem::parse(TiXmlElement* element)
    {
        m_name = helpers::readAttributeText(element, "name");
        m_itemID = helpers::readAttributeText(element, "itemID");
        m_linkageExportForRS = helpers::readAttributeText(element, "linkageExportForRS");
        m_linkageIdentifier = helpers::readAttributeText(element, "linkageIdentifier");
        m_linkageURL = helpers::readAttributeText(element, "linkageURL");
        m_sourceExternalFilepath = helpers::readAttributeText(element, "sourceExternalFilepath");
        m_sourceLastImported = helpers::readAttributeText(element, "sourceLastImported");
        m_allowSmoothing = helpers::readAttributeText(element, "allowSmoothing");
        m_useImportedJPEGData = helpers::readAttributeText(element, "useImportedJPEGData");
        m_compressionType = helpers::readAttributeText(element, "compressionType");
        m_originalCompressionType = helpers::readAttributeText(element, "originalCompressionType");
        m_quality = helpers::readAttributeText(element, "quality");
        m_href = helpers::readAttributeText(element, "href");
        m_bitmapDataHRef = helpers::readAttributeText(element, "bitmapDataHRef");
        m_frameRight = helpers::readAttributeText(element, "frameRight");
        m_frameBottom = helpers::readAttributeText(element, "frameBottom");

        Logger::get().write("Bitmap \"%s\".", m_name.c_str());

        return true;
    }

};
};