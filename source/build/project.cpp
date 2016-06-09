#include "project.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "dom/document.hpp"
#include "publish.hpp"

namespace iris {

    Project::Project(JSContext* context)
        : m_context(context)
    {
    }

    Project::~Project()
    {
    }

    bool Project::load(const std::string& filePath)
    {
        // Validate project type

        static const char* Extension = ".xfl";
        static const size_t ExtensionLength = strlen(Extension);

        if (filePath.length() < ExtensionLength ||
            filePath.compare(filePath.length() - ExtensionLength, ExtensionLength, Extension) != 0)
        {
            return false;
        }

        // Create intermediate directory

        m_projectPath = filePath;
        const size_t last_slash = m_projectPath.find_last_of('\\');
        if (last_slash != std::string::npos)
        {
            m_projectPath.erase(last_slash, m_projectPath.length() - last_slash);
        }

        m_intermediatePath = m_projectPath + "\\intermediate";

        helpers::createDirectory(m_intermediatePath);

        // Load project settings

        m_publish = std::shared_ptr<Publish>(new Publish(*this));
        if (!m_publish->load(m_projectPath + "\\PublishSettings.xml"))
        {
            return false;
        }

        // Load document

        m_document = std::shared_ptr<dom::Document>(new dom::Document(*this));
        if (!m_document->load(m_projectPath + "\\DOMDocument.xml"))
        {
            return false;
        }

        return true;
    }

    std::string Project::getTaskIntermediatePath() const
    {
        char filename[_MAX_FNAME] = { 0 };
        _splitpath(m_projectPath.c_str(), nullptr, nullptr, filename, nullptr);

        return m_intermediatePath + "\\" + filename + ".tlog";
    }

    std::string Project::getTaskSourcePath() const
    {
        return m_projectPath;
    }

    std::string Project::getTaskCommand() const
    {
        return m_projectPath;
    }

    std::vector<std::shared_ptr<Task>> Project::getTaskDependencies() const
    {
        std::vector<std::shared_ptr<Task>> dependencies;

        return dependencies;
    }

};