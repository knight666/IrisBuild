#ifndef _HELPERS_H_
#define _HELPERS_H_

#include "interface.h"

JSBool valueToString(JSContext* context, jsval input, char** target, size_t* targetSize);
JSBool stringToValue(JSContext* context, const char* input, size_t inputSize, jsval* target);

#endif