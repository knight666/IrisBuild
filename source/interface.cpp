#include "interface.hpp"

#include "build/project.hpp"
#include "build/solution.hpp"
#include "build/treevisitor.hpp"
#include "logging/logger.hpp"
#include "application.hpp"
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

    bool success = Application::get().initialize(helpers::uriToAbsolute(configurationPath));
    helpers::toJsfl(context, success, *result);

    return JS_TRUE;
}

JSBool createSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::fromJsfl(context, argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"createSolution\".");

        return JS_FALSE;
    }

    bool success = Application::get().createSolution(helpers::uriToAbsolute(path));
    helpers::toJsfl(context, success, *result);

    return JS_TRUE;
}

JSBool loadSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::fromJsfl(context, argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"loadSolution\".");

        return JS_FALSE;
    }

    bool success = Application::get().getSolution()->load(helpers::uriToAbsolute(path));
    helpers::toJsfl(context, success, *result);

    return JS_TRUE;
}

JSBool saveSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::fromJsfl(context, argumentList[0], path))
    {
        IRIS_LOG_ERROR("Invalid arguments supplied for \"loadSolution\".");

        return JS_FALSE;
    }

    bool success = Application::get().getSolution()->save(helpers::uriToAbsolute(path));
    helpers::toJsfl(context, success, *result);

    return JS_TRUE;
}

JSBool verifySolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    bool success = Application::get().getSolution()->verify();
    helpers::toJsfl(context, success, *result);

    return JS_TRUE;
}

JSBool getSolutionTreeDataProvider(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    TreeVisitor printer;
    Application::get().getSolution()->accept(printer);

    IRIS_LOG_TRACE("serialized: \"%s\"", printer.getSerialized().c_str());

    helpers::toJsfl(context, printer.getSerialized(), *result);

    return JS_TRUE;
}

JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::fromJsfl(context, argumentList[0], path))
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

    helpers::toJsfl(context, status, *result);

    return JS_TRUE;
}