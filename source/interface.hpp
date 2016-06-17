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
IRIS_INTERFACE(getSettingInt, 1)
IRIS_INTERFACE(getSettingString, 1)
IRIS_INTERFACE(setSettingInt, 2)
IRIS_INTERFACE(setSettingString, 2)
IRIS_INTERFACE(loadProject, 1)

#undef IRIS_INTERFACE
#undef IRIS_WIDEN