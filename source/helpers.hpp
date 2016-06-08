#pragma once

#include "interface.hpp"

JSBool valueToString(JSContext* context, jsval input, char** target, size_t* targetSize);
JSBool stringToValue(JSContext* context, const char* input, size_t inputSize, jsval* target);