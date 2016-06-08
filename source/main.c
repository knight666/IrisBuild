// C/STL
#include <stdlib.h>

// utf8rewind
#include <utf8rewind.h>

// Flash API
#include "mm_jsapi.h"

JSBool valueToString(JSContext* context, jsval input, char** target, size_t* targetSize)
{
    unsigned int inputWideLength = 0;
    unsigned short* inputWide = JS_ValueToString(context, input, &inputWideLength);
    int32_t errors = 0;

    if (inputWide == NULL ||
        inputWideLength == 0)
    {
        return JS_FALSE;
    }

    if ((*targetSize = widetoutf8(inputWide, inputWideLength * sizeof(wchar_t), NULL, 0, &errors)) == 0 ||
        errors != UTF8_ERR_NONE)
    {
        return JS_FALSE;
    }

    *target = (char*)malloc(*targetSize);
    widetoutf8(inputWide, inputWideLength * sizeof(wchar_t), *target, *targetSize, NULL);

    return JS_TRUE;
}

JSBool stringToValue(JSContext* context, const char* input, size_t inputSize, jsval* target)
{
    wchar_t* outputWide = NULL;
    size_t outputWideSize = 0;
    int32_t errors = 0;
    JSBool result;

    if ((outputWideSize = utf8towide(input, inputSize, NULL, 0, &errors)) == 0 ||
        errors != UTF8_ERR_NONE)
    {
        return JS_FALSE;
    }

    outputWide = (wchar_t*)malloc(outputWideSize);
    utf8towide(input, inputSize, outputWide, outputWideSize, NULL);

    result = JS_StringToValue(context, outputWide, outputWideSize, target);

    free(outputWide);

    return result;
}

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

MM_STATE

void MM_Init()
{
    JS_DefineFunction(L"loadProject", loadProject, 1);
}

void MM_Terminate()
{
}