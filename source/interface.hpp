/*
    Copyright (c) 2016 Bigpoint GmbH

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifdef IRIS_IMPLEMENT_FUNCTIONS
    #define IRIS_WIDEN(_text) L ## _text
    #define IRIS_INTERFACE(_name, _argumentCount) \
        JS_DefineFunction(IRIS_WIDEN(#_name), _name, _argumentCount);
#else
    #define IRIS_INTERFACE(_name, _argumentCount) \
        extern "C" JSBool _name (JSContext* context, JSObject* target, unsigned int argumentCount, jsval* argumentList, jsval* result);
#endif

IRIS_INTERFACE(initialize, 1)
IRIS_INTERFACE(createSolution, 1)
IRIS_INTERFACE(loadSolution, 1)
IRIS_INTERFACE(saveSolution, 1)
IRIS_INTERFACE(verifySolution, 0)
IRIS_INTERFACE(getSolutionTreeDataProvider, 0)
IRIS_INTERFACE(addProject, 1)
IRIS_INTERFACE(removeProject, 1)
IRIS_INTERFACE(buildProjects, 0)
IRIS_INTERFACE(getSettingInt, 1)
IRIS_INTERFACE(getSettingString, 1)
IRIS_INTERFACE(setSettingInt, 2)
IRIS_INTERFACE(setSettingString, 2)
IRIS_INTERFACE(loadProject, 1)

#undef IRIS_INTERFACE
#undef IRIS_WIDEN