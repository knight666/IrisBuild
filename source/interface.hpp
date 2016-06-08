#pragma once

// C/STL
#include <stdlib.h>
#include <string>

extern "C" {

    // utf8rewind
    #include <utf8rewind.h>

    // Flash API
    #include "mm_jsapi.h"

}

// Public interface
extern "C" JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);