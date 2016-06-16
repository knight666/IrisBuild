#pragma once

// C
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// STL
#include <fstream>
#include <map>
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

#define IRIS_SAVE_VERSION 1

// Public interface
extern "C" JSBool initialize(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool createSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool loadSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool saveSolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool verifySolution(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool getSolutionTreeDataProvider(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool addProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool removeProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
extern "C" JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);