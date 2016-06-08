#include "interface.h"

#include "helpers.h"

JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    char* path = NULL;
    size_t pathSize = 0;
    JSBool success = JS_TRUE;

    if (argumentCount < 1 ||
        valueToString(context, argumentList[0], &path, &pathSize) == JS_FALSE)
    {
        success = JS_FALSE;
        goto cleanup;
    }

    stringToValue(context, path, pathSize, result);

cleanup:
    if (path != NULL)
    {
        free(path);
    }

    return success;
}