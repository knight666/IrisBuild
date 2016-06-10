#pragma once

// C
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// STL
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Windows
#include <windows.h>
#include <ShlObj.h>

extern "C" {

    // utf8rewind
    #include <utf8rewind.h>

    // Flash API
    #include "mm_jsapi.h"

}

// TinyXML
#include <tinyxml.h>

// Public interface
extern "C" JSBool initialize(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);