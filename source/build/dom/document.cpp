#include "document.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"
#include "../project.hpp"
#include "../visitor.hpp"
#include "bitmapitem.hpp"
#include "symbol.hpp"

namespace iris {
namespace dom {

    Document::Document(Project& project)
        : m_project(project)
    {
    }

    Document::~Document()
    {
    }

    bool Document::accept(Visitor& visitor)
    {
        return visitor.visitEnter(*this) && visitor.visitLeave(*this);
    }

    bool Document::load(const std::string& filePath)
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

        m_filePath = filePath;

        TiXmlElement* media = m_document->RootElement()->FirstChildElement("media");
        if (media != nullptr)
        {
            XML_FOR_EACH(media, "DOMBitmapItem", bitmap_element)
            {
                std::shared_ptr<BitmapItem> bitmap(new BitmapItem(*this));

                if (!bitmap->parse(bitmap_element))
                {
                    IRIS_LOG_ERROR("Failed to parse bitmap item.");

                    return false;
                }

                m_dependencies.push_back(bitmap);
            }
        }

        TiXmlElement* symbols = m_document->RootElement()->FirstChildElement("symbols");
        if (symbols != nullptr)
        {
            XML_FOR_EACH(symbols, "Include", symbol_element)
            {
                std::shared_ptr<Symbol> symbol(new Symbol(*this));

                if (!symbol->parse(symbol_element))
                {
                    IRIS_LOG_ERROR("Failed to parse symbol.");

                    return false;
                }

                m_dependencies.push_back(symbol);
            }
        }

        return true;
    }

    bool Document::onTaskBuild(JSObject* context)
    {
        return true;
    }

    std::string Document::getTaskIntermediatePath() const
    {
        return m_project.getIntermediatePath() + "\\DOMDocument.tlog";
    }

    std::string Document::getTaskSourcePath() const
    {
        return m_filePath;
    }

    std::string Document::getTaskCommand() const
    {
        TiXmlElement* root = m_document->RootElement();

        std::string result = helpers::readAttributeText(root, "backgroundColor");
        result += " " + helpers::readAttributeText(root, "width");
        result += " " + helpers::readAttributeText(root, "height");
        result += " " + helpers::readAttributeText(root, "frameRate");
        result += " " + helpers::readAttributeText(root, "currentTimeline");
        result += " " + helpers::readAttributeText(root, "xflVersion");
        result += " " + helpers::readAttributeText(root, "creatorInfo");
        result += " " + helpers::readAttributeText(root, "platform");
        result += " " + helpers::readAttributeText(root, "versionInfo");
        result += " " + helpers::readAttributeText(root, "majorVersion");
        result += " " + helpers::readAttributeText(root, "minorVersion");
        result += " " + helpers::readAttributeText(root, "buildNumber");
        result += " " + helpers::readAttributeText(root, "viewAngle3D");
        result += " " + helpers::readAttributeText(root, "sharedLibraryURL");
        result += " " + helpers::readAttributeText(root, "nextSceneIdentifier");
        result += " " + helpers::readAttributeText(root, "playOptionsPlayLoop");
        result += " " + helpers::readAttributeText(root, "playOptionsPlayPages");
        result += " " + helpers::readAttributeText(root, "playOptionsPlayFrameActions");

        return result;
    }

    std::vector<std::shared_ptr<Task>> Document::getTaskDependencies() const
    {
        return m_dependencies;
    }

};
};