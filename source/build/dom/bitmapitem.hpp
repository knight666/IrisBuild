#pragma once

#include "../../interface.hpp"

namespace iris {
    namespace dom {
        class Document;
    };
};

namespace iris {
namespace dom {

    class BitmapItem
    {

    public:

        BitmapItem(Document& document);
        ~BitmapItem();

        bool parse(TiXmlElement* element);

    private:

        Document& m_document;
        TiXmlElement* m_element;

        std::string m_name;
        std::string m_itemID;
        std::string m_linkageExportForRS;
        std::string m_linkageIdentifier;
        std::string m_linkageURL;
        std::string m_sourceExternalFilepath;
        std::string m_sourceLastImported;
        std::string m_allowSmoothing;
        std::string m_useImportedJPEGData;
        std::string m_compressionType;
        std::string m_originalCompressionType;
        std::string m_quality;
        std::string m_href;
        std::string m_bitmapDataHRef;
        std::string m_frameRight;
        std::string m_frameBottom;

    };

};
};