#include "interface.hpp"

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

    helpers::stringToValue(*context, path, *result);

    return JS_TRUE;
}