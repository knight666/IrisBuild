#include "bitmapitem.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"
#include "../project.hpp"
#include "document.hpp"

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
        m_linkageIdentifier = helpers::readAttributeText(element, "linkageIdentifier");
        m_linkageURL = helpers::readAttributeText(element, "linkageURL");
        m_sourceExternalFilepath = helpers::readAttributeText(element, "sourceExternalFilepath");
        m_href = helpers::readAttributeText(element, "href");

        IRIS_LOG_TRACE("Bitmap \"%s\".", m_name.c_str());
        IRIS_LOG_INSANE("\tlinkageIdentifier: \"%s\".", m_linkageIdentifier.c_str());
        IRIS_LOG_INSANE("\tlinkageURL: \"%s\".", m_linkageURL.c_str());
        IRIS_LOG_INSANE("\tsourceExternalFilepath: \"%s\".", m_sourceExternalFilepath.c_str());
        IRIS_LOG_INSANE("\thref: \"%s\".", m_href.c_str());

        m_element = element;

        return true;
    }

    bool BitmapItem::onTaskBuild(JSObject* context)
    {
        return true;
    }

    std::string BitmapItem::getTaskIntermediatePath() const
    {
        char directory[_MAX_DIR] = { 0 };
        char filename[_MAX_FNAME] = { 0 };
        _splitpath(m_sourceExternalFilepath.c_str(), nullptr, directory, filename, nullptr);

        return helpers::absolutePath(m_document.getProject().getIntermediatePath() + "\\" + directory + "\\" + filename + ".tlog");
    }

    std::string BitmapItem::getTaskSourcePath() const
    {
        return helpers::absolutePath(m_document.getProject().getProjectPath() + m_sourceExternalFilepath);
    }

    std::string BitmapItem::getTaskCommand() const
    {
        std::string result = helpers::readAttributeText(m_element, "name");
        result += " " + helpers::readAttributeText(m_element, "itemID");
        result += " " + helpers::readAttributeText(m_element, "linkageExportForRS");
        result += " " + helpers::readAttributeText(m_element, "linkageIdentifier");
        result += " " + helpers::readAttributeText(m_element, "linkageURL");
        result += " " + helpers::readAttributeText(m_element, "sourceExternalFilepath");
        result += " " + helpers::readAttributeText(m_element, "sourceLastImported");
        result += " " + helpers::readAttributeText(m_element, "allowSmoothing");
        result += " " + helpers::readAttributeText(m_element, "useImportedJPEGData");
        result += " " + helpers::readAttributeText(m_element, "compressionType");
        result += " " + helpers::readAttributeText(m_element, "originalCompressionType");
        result += " " + helpers::readAttributeText(m_element, "quality");
        result += " " + helpers::readAttributeText(m_element, "href");
        result += " " + helpers::readAttributeText(m_element, "bitmapDataHRef");
        result += " " + helpers::readAttributeText(m_element, "frameRight");
        result += " " + helpers::readAttributeText(m_element, "frameBottom");

        return result;
    }

    std::vector<std::shared_ptr<Task>> BitmapItem::getTaskDependencies() const
    {
        std::vector<std::shared_ptr<Task>> dependencies;

        return dependencies;
    }

};
};