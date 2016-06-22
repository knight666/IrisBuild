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

            ss_build << "var errors_uri = '" << helpers::absolutePathToUri(project->getIntermediatePath() + "\\errors.log") << "';" << std::endl;
            ss_build << "fl.trace(errors_uri);" << std::endl;
            ss_build << "fl.publishDocument('" << helpers::absolutePathToUri(project->getFilePath()) << "');" << std::endl;
            ss_build << "if (FLfile.write(errors_uri, '')) { fl.compilerErrors.save(errors_uri, false); }" << std::endl;
            ss_build << "FLfile.read(errors_uri, true);";

            jsval errors = IRIS_JS_EVAL(m_context, ss_build.str());

            std::string s_errors;
            if (Scripting::get().fromJsfl(errors, s_errors))
            {
                IRIS_LOG_ERROR("Errors: %s", s_errors.c_str());

                ss_log << "fl.trace(\"" << index << "> " << s_errors << "\");" << std::endl;
            }

            IRIS_LOG_TRACE("errors %d errorsString %s", errors, s_errors.c_str());

            index++;
        }

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