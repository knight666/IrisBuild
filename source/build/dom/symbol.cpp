#include "symbol.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"
#include "../project.hpp"
#include "document.hpp"

namespace iris {
namespace dom {

    Symbol::Symbol(Document& document)
        : m_document(document)
        , m_element(nullptr)
    {
    }

    Symbol::~Symbol()
    {
    }

    bool Symbol::parse(TiXmlElement* element)
    {
        m_href = helpers::readAttributeText(element, "href");

        m_element = element;

        return true;
    }

    bool Symbol::onTaskBuild(JSObject* context)
    {
        return true;
    }

    std::string Symbol::getTaskIntermediatePath() const
    {
        char directory[_MAX_DIR] = { 0 };
        char filename[_MAX_FNAME] = { 0 };
        _splitpath(m_href.c_str(), nullptr, directory, filename, nullptr);

        return helpers::absolutePath(m_document.getProject().getIntermediatePath() + "\\" + directory + "\\" + filename + ".tlog");
    }

    std::string Symbol::getTaskSourcePath() const
    {
        return helpers::absolutePath(m_document.getProject().getProjectPath() + m_href);
    }

    std::string Symbol::getTaskCommand() const
    {
        std::string result = helpers::readAttributeText(m_element, "href");
        result += " " + helpers::readAttributeText(m_element, "itemID");
        result += " " + helpers::readAttributeText(m_element, "lastModified");

        return result;
    }

    std::vector<std::shared_ptr<Task>> Symbol::getTaskDependencies() const
    {
        std::vector<std::shared_ptr<Task>> dependencies;

        return dependencies;
    }

};
};