#include "interface.hpp"

#include "build/project.hpp"
#include "helpers.hpp"

using namespace iris;

JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    std::string path;

    if (argumentCount < 1 ||
        !helpers::valueToString(*context, argumentList[0], path))
    {
        return JS_FALSE;
    }

    Project project(context);
    if (!project.load(path))
    {
        return JS_TRUE;
    }

    helpers::stringToValue(*context, project.getIntermediatePath(), *result);

    return JS_TRUE;
}