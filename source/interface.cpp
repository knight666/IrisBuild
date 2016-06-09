#include "interface.hpp"

#include "build/project.hpp"
#include "build/solution.hpp"
#include "logging/logger.hpp"
#include "helpers.hpp"

using namespace iris;

JSBool initialize(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string configurationPath;

    if (argumentCount < 1 ||
        !helpers::valueToString(*context, argumentList[0], configurationPath))
    {
        return JS_FALSE;
    }

    Logger::get().setFilePath(configurationPath + "IrisBuild.log");
    Logger::get().write("Opening log.");

    return JS_TRUE;
}

JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::valueToString(*context, argumentList[0], path))
    {
        return JS_FALSE;
    }

    std::shared_ptr<Project> project(new Project(context));

    Solution::get().addProject(project);

    if (!project->load(path))
    {
        return JS_TRUE;
    }

    project->check();

    helpers::stringToValue(*context, project->getIntermediatePath(), *result);

    return JS_TRUE;
}