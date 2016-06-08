#include "interface.h"

MM_STATE

void MM_Init()
{
    JS_DefineFunction(L"loadProject", loadProject, 1);
}

void MM_Terminate()
{
}