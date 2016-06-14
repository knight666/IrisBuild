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
        IRIS_LOG_ERROR("Invalid arguments supplied for \"initialize\".");

        return JS_FALSE;
    }

    Logger::get().setFilePath(configurationPath + "IrisBuild.log");
    IRIS_LOG_INFO("Opening log.");

    return JS_TRUE;
}

JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::valueToString(*context, argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"loadProject\".");

        return JS_FALSE;
    }

    IRIS_LOG_INFO("Loading project \"%s\".", path.c_str());

    std::shared_ptr<Project> project(new Project(context));

    Solution::get().addProject(project);

    if (!project->parse(path))
    {
        IRIS_LOG_ERROR("Failed to load the project.");

        return JS_TRUE;
    }

    bool status = project->check();

    IRIS_LOG_INFO("Project is %s.", status ? "up-to-date" : "out-of-date");

    helpers::stringToValue(*context, status ? "true" : "false", *result);

    return JS_TRUE;
}