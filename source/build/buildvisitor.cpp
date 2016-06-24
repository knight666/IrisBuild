#include "buildvisitor.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"
#include "../scripting.hpp"
#include "project.hpp"
#include "solution.hpp"

namespace iris {

    BuildVisitor::BuildVisitor(JSObject* context)
        : m_context(context)
    {

    }

    BuildVisitor::~BuildVisitor()
    {

    }

    bool BuildVisitor::visitEnter(Solution& solution)
    {
        m_projects.clear();

        return true;
    }

    bool BuildVisitor::visitLeave(Solution& solution)
    {
        std::stringstream ss_log;
        size_t index = 1;

        for (Project* project : m_projects)
        {
            char filename[_MAX_FNAME] = { 0 };
            _splitpath(project->getFilePath().c_str(), nullptr, nullptr, filename, nullptr);

            IRIS_LOG_INFO("Building \"%s\".", filename);

            ss_log << "fl.trace(\"" << index << "> Building '" << filename << "'\");" << std::endl;

            std::stringstream ss_build;

            std::string errors_path = project->getIntermediatePath() + "\\errors.log";

            ss_build << "var errors_uri = '" << helpers::absolutePathToUri(errors_path) << "';" << std::endl;
            ss_build << "fl.publishDocument('" << helpers::absolutePathToUri(project->getFilePath()) << "');" << std::endl;
            ss_build << "if (FLfile.write(errors_uri, '')) { fl.compilerErrors.save(errors_uri, false); }";

            IRIS_JS_EVAL(m_context, ss_build.str());

            std::string errors;

            if (helpers::fileExists(errors_path))
            {
                std::ifstream file(errors_path, std::ios::in | std::ios::binary);
                std::stringstream file_stream;
                file_stream << file.rdbuf();
                file.close();

                errors = file_stream.str();

                ss_log << "fl.trace(\"" << index << "> " << errors << "\");" << std::endl;
            }

            IRIS_LOG_TRACE("\"%s\" errorsString %s", filename, errors.c_str());

            size_t build_failed = errors.find("**Error**");
            if (build_failed != std::string::npos)
            {
                ss_log << "fl.trace(\"" << index << "> Build FAILED.\");" << std::endl;

                break;
            }

            index++;
        }

        IRIS_LOG_TRACE("%s", ss_log.str().c_str());

        IRIS_JS_EVAL(m_context, ss_log.str());

        return true;
    }

    bool BuildVisitor::visitEnter(Project& project)
    {
        if (!project.check())
        {
            m_projects.push_back(&project);
        }

        return true;
    }

};