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
        for (Project* project : m_projects)
        {
            char filename[_MAX_FNAME] = { 0 };
            _splitpath(project->getFilePath().c_str(), nullptr, nullptr, filename, nullptr);

            IRIS_LOG_INFO("Building \"%s\".", filename);

            std::string uri_errors_log = helpers::absolutePathToUri(project->getIntermediatePath() + "\\errors.log");

            std::stringstream ss_build;

            ss_build << "fl.publishDocument('" << helpers::absolutePathToUri(project->getFilePath()) << "');" << std::endl;
            ss_build << "fl.compilerErrors.save('" << uri_errors_log << "', true);";

            IRIS_JS_EVAL(m_context, ss_build.str());

            std::stringstream ss_read;

            ss_read << "FLfile.read('" << uri_errors_log << "', true);";

            jsval errors = IRIS_JS_EVAL(m_context, ss_read.str());

            std::string s_errors;
            if (Scripting::get().fromJsfl(errors, s_errors))
            {
                IRIS_LOG_ERROR("Errors: %s", s_errors.c_str());
            }

            IRIS_LOG_TRACE("errors %d errorsString %s", errors, s_errors.c_str());
        }

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