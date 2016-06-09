#include "build/solution.hpp"

MM_STATE

void MM_Init()
{
    JS_DefineFunction(L"loadProject", loadProject, 1);

    iris::Solution::create();
}

void MM_Terminate()
{
    iris::Solution::destroy();
}