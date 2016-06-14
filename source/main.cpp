#include "build/solution.hpp"
#include "logging/logger.hpp"

MM_STATE

void MM_Init()
{
    JS_DefineFunction(L"initialize", initialize, 1);
    JS_DefineFunction(L"loadSolution", loadSolution, 1);
    JS_DefineFunction(L"saveSolution", saveSolution, 1);
    JS_DefineFunction(L"loadProject", loadProject, 1);

    iris::Logger::create();
    iris::Solution::create();
}

void MM_Terminate()
{
    iris::Solution::destroy();
    iris::Logger::destroy();
}