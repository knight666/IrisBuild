#include "main.hpp"

#include "interface.hpp"

#include "build/project.hpp"
#include "build/solution.hpp"
#include "build/buildvisitor.hpp"
#include "build/treevisitor.hpp"
#include "logging/logger.hpp"
#include "application.hpp"
#include "helpers.hpp"
#include "scripting.hpp"

using namespace iris;

JSBool initialize(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    Scripting::get().setContext(context);

    std::string configurationPath;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], configurationPath))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"initialize\".");

        return JS_FALSE;
    }

    bool success = Application::get().initialize(helpers::uriToAbsolute(configurationPath));
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool createSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"createSolution\".");

        return JS_FALSE;
    }

    bool success = Application::get().createSolution(helpers::uriToAbsolute(path));
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool loadSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"loadSolution\".");

        return JS_FALSE;
    }

    bool success = Application::get().getSolution()->load(helpers::uriToAbsolute(path));
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool saveSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"saveSolution\".");

        return JS_FALSE;
    }

    bool success = Application::get().getSolution()->save(helpers::uriToAbsolute(path));
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool verifySolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    bool success = Application::get().getSolution()->verify();
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool getSolutionTreeDataProvider(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    TreeVisitor printer;
    Application::get().getSolution()->accept(printer);

    IRIS_LOG_TRACE("serialized: \"%s\"", printer.getSerialized().c_str());

    Scripting::get().toJsfl(printer.getSerialized(), *result);

    return JS_TRUE;
}

JSBool addProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"addProject\".");

        return JS_FALSE;
    }

    std::shared_ptr<Project> project = Application::get().getSolution()->addProject(helpers::uriToAbsolute(path));
    Scripting::get().toJsfl(project != nullptr, *result);

    return JS_TRUE;
}

JSBool removeProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"removeProject\".");

        return JS_FALSE;
    }

    bool success = Application::get().getSolution()->removeProject(helpers::uriToAbsolute(path));
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool buildProjects(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    bool success = Application::get().getSolution()->build(target);
    Scripting::get().toJsfl(success, *result);

    return JS_TRUE;
}

JSBool getSettingInt(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    double setting;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], setting))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"getSettingInt\".");

        return JS_FALSE;
    }

    switch ((uint32_t)setting)
    {

    case IRIS_SETTING_LOGGER_LEVEL:
        {
            Logger::Level level = Logger::get().getMaximumLevel();

            Scripting::get().toJsfl((double)level, *result);

        } break;

    default:
        return JS_FALSE;

    }

    return JS_TRUE;
}

JSBool getSettingString(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    double setting;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], setting))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"getSettingString\".");

        return JS_FALSE;
    }

    return JS_TRUE;
}

JSBool setSettingInt(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    double setting;
    double value;

    // For some reason the second argument from the list should be skipped if
    // the first value is a double.
    //
    // This SDK is insane...

    if (argumentCount < 2 ||
        !Scripting::get().fromJsfl(argumentList[0], setting) ||
        !Scripting::get().fromJsfl(argumentList[2], value))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"setSettingInt\".");

        return JS_FALSE;
    }

    int32_t value_cast = (int32_t)value;

    switch ((uint32_t)setting)
    {

    case IRIS_SETTING_LOGGER_LEVEL:
    {
        Logger::get().setMaximumLevel((Logger::Level)value_cast);

    } break;

    default:
        return JS_FALSE;

    }

    return JS_TRUE;
}

JSBool setSettingString(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    double setting;
    std::string value;

    if (argumentCount < 2 ||
        !Scripting::get().fromJsfl(argumentList[0], setting) ||
        !Scripting::get().fromJsfl(argumentList[1], value))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"setSettingString\".");

        return JS_FALSE;
    }

    return JS_TRUE;
}

JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !Scripting::get().fromJsfl(argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"loadProject\".");

        return JS_FALSE;
    }

    path = helpers::uriToAbsolute(path);

    IRIS_LOG_INFO("Loading project \"%s\".", path.c_str());

    std::shared_ptr<Project> project(new Project(*Application::get().getSolution()));

    if (!project->parse(path))
    {
        IRIS_LOG_ERROR("Failed to load the project.");

        return JS_TRUE;
    }

    bool status = project->check();

    IRIS_LOG_INFO("Project is %s.", status ? "up-to-date" : "out-of-date");

    Scripting::get().toJsfl(status, *result);

    return JS_TRUE;
}