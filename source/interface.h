#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_

// C/STL
#include <stdlib.h>

// utf8rewind
#include <utf8rewind.h>

// Flash API
#include "mm_jsapi.h"

// Public interface
JSBool loadProject(JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);

#endif