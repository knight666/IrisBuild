/*
    Copyright (c) 2016 Bigpoint GmbH

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

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