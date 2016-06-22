#include "logging/logger.hpp"
#include "application.hpp"
#include "main.hpp"
#include "scripting.hpp"

#include "interface.hpp"

MM_STATE

void MM_Init()
{
#define IRIS_IMPLEMENT_FUNCTIONS
    #include "interface.hpp"
#undef IRIS_IMPLEMENT_FUNCTIONS

    iris::Logger::create();
    iris::Application::create();
    iris::Scripting::create();
}

void MM_Terminate()
{
    iris::Scripting::destroy();
    iris::Application::destroy();
    iris::Logger::destroy();
}