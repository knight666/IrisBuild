#pragma once

// C
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// STL
#include <fstream>
#include <memory>
#include <string>
#include <vector>

// Windows
#include <windows.h>

extern "C" {

    // utf8rewind
    #include <utf8rewind.h>

    // Flash API
    #include "mm_jsapi.h"

}

// Public interface
extern "C" JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);