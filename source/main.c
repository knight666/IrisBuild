#include "mm_jsapi.h"

#define IRIS_API __declspec(dllexport)

JSBool computeSum(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result)
{
    long a, b, sum;

    // Make sure the right number of arguments were passed in
    if (argumentCount != 2)
        return JS_FALSE;

    // Convert the two arguments from jsvals to longs
    if (JS_ValueToInteger(context, argumentList[0], &a) == JS_FALSE ||
        JS_ValueToInteger(context, argumentList[1], &b) == JS_FALSE)
        return JS_FALSE;

    // Perform the actual work
    sum = a + b;

    // Package the return value as a jsval
    *result = JS_IntegerToValue(sum);

    // Indicate success
    return JS_TRUE;
}

MM_STATE

void MM_Init()
{
    JS_DefineFunction(L"computeSum", computeSum, 2);
}

void MM_Terminate()
{
}