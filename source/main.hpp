#pragma once

// C
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// STL
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Windows
#include <windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>

extern "C" {
    // utf8rewind
    #include <utf8rewind.h>

    // Flash API
    #include "mm_jsapi.h"
};

// TinyXML
#include <tinyxml.h>

// Settings
#define IRIS_SAVE_VERSION 1

#define IRIS_SETTING_LOGGER_LEVEL  1