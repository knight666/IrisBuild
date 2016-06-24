#include "project.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "../scripting.hpp"
#include "dom/document.hpp"
#include "publish.hpp"
#include "solution.hpp"
#include "visitor.hpp"

namespace iris {

    Project::Project(Solution& solution)
        : m_solution(solution)
    {
    }

    Project::~Project()
    {
    }

    bool Project::parse(const std::string& filePath)
    {
        static const char* Extension = ".xfl";
        static const size_t ExtensionLength = strlen(Extension);

        if (filePath.length() < ExtensionLength ||
            filePath.compare(filePath.length() - ExtensionLength, ExtensionLength, Extension) != 0)
        {
            IRIS_LOG_ERROR("Project \"%s\" is not an uncompressed Flash file.", filePath.c_str());

            return false;
        }

        m_filePath = filePath;

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
            IRIS_LOG_ERROR("Failed to parse publish settings.");

            return false;
        }

        // Load document

        m_document = std::shared_ptr<dom::Document>(new dom::Document(*this));
        if (!m_document->load(m_projectPath + "\\DOMDocument.xml"))
        {
            IRIS_LOG_ERROR("Failed to parse DOM document.");

            return false;
        }

        return true;
    }

    bool Project::accept(Visitor& visitor)
    {
        return visitor.visitEnter(*this) && m_publish->accept(visitor) && m_document->accept(visitor) && visitor.visitLeave(*this);
    }

    bool Project::load(TiXmlElement* element, uint32_t version)
    {
        std::string path = helpers::readAttributeText(element, "path");
        IRIS_LOG_TRACE("path: %s", path.c_str());

        std::string file_path = helpers::absolutePath(m_solution.getWorkingDirectory() + path);
        if (!parse(file_path))
        {
            return false;
        }

        return true;
    }

    bool Project::save(TiXmlElement* element, uint32_t version)
    {
        std::string relative = helpers::relativePath(m_solution.getWorkingDirectory(), m_filePath);

        IRIS_LOG_TRACE("workingDirectory %s filePath %s relative %s", m_solution.getWorkingDirectory().c_str(), m_filePath.c_str(), relative.c_str());

        TiXmlElement* project_element = new TiXmlElement("Project");
        project_element->SetAttribute("path", relative.c_str());
        element->LinkEndChild(project_element);

        return true;
    }

    bool Project::onTaskBuild(JSObject* context)
    {
        std::string relative = helpers::relativePath(m_solution.getWorkingDirectory(), m_filePath);

        IRIS_LOG_INFO("Building \"%s\".", relative.c_str());

        std::string errors_path = m_intermediatePath + "\\errors.log";

        std::stringstream ss_build;
        ss_build << "var errors_uri = '" << helpers::absolutePathToUri(errors_path) << "';" << std::endl;
        ss_build << "fl.publishDocument('" << helpers::absolutePathToUri(m_filePath) << "');" << std::endl;
        ss_build << "if (FLfile.write(errors_uri, '')) { fl.compilerErrors.save(errors_uri, false); }";
        IRIS_JS_EVAL(context, ss_build.str());

        std::string errors;

        if (helpers::fileExists(errors_path))
        {
            std::ifstream file(errors_path, std::ios::in | std::ios::binary);
            std::stringstream file_stream;
            file_stream << file.rdbuf();
            file.close();

            errors = file_stream.str();
        }

        return errors.find("**Error**") == std::string::npos;
    }

    std::string Project::getTaskIntermediatePath() const
    {
        char filename[_MAX_FNAME] = { 0 };
        _splitpath(m_projectPath.c_str(), nullptr, nullptr, filename, nullptr);

        return m_intermediatePath + "\\" + filename + ".tlog";
    }

    std::string Project::getTaskSourcePath() const
    {
        return m_filePath;
    }

    std::string Project::getTaskCommand() const
    {
        return m_projectPath;
    }

    std::vector<std::shared_ptr<Task>> Project::getTaskDependencies() const
    {
        std::vector<std::shared_ptr<Task>> dependencies;

        dependencies.push_back(m_document);

        return dependencies;
    }

};