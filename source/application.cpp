#include "application.hpp"

namespace iris {

    Application* Application::s_instance = nullptr;

    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    Application& Application::get()
    {
        return *s_instance;
    }

    void Application::create()
    {
        s_instance = new Application();
    }

    void Application::destroy()
    {
        delete s_instance;
        s_instance = nullptr;
    }

    std::shared_ptr<Solution> Application::createSolution(const std::string& filePath)
    {
        return nullptr;
    }

    std::shared_ptr<Solution> Application::loadSolution(const std::string& filePath)
    {
        return nullptr;
    }

};