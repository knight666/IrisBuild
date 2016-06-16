#include "logging/logger.hpp"
#include "application.hpp"

MM_STATE

void MM_Init()
{
    JS_DefineFunction(L"initialize", initialize, 1);
    JS_DefineFunction(L"createSolution", createSolution, 1);
    JS_DefineFunction(L"loadSolution", loadSolution, 1);
    JS_DefineFunction(L"saveSolution", saveSolution, 1);
    JS_DefineFunction(L"verifySolution", verifySolution, 0);
    JS_DefineFunction(L"getSolutionTreeDataProvider", getSolutionTreeDataProvider, 0);
    JS_DefineFunction(L"loadProject", loadProject, 1);

    iris::Logger::create();
    iris::Application::create();
}

void MM_Terminate()
{
    iris::Application::destroy();
    iris::Logger::destroy();
}