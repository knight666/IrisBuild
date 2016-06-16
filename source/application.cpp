#include "application.hpp"

#include "build/solution.hpp"
#include "logging/logger.hpp"

namespace iris {

    Application* Application::s_instance = nullptr;

    Application::Application()
        : m_solution(new Solution())
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

    bool Application::initialize(const std::string& configurationPath)
    {
        Logger::get().setFilePath(configurationPath + "IrisBuild.log");
        IRIS_LOG_INFO("Opening log.");

        m_configurationPath = configurationPath;

        return true;
    }

    std::shared_ptr<Solution> Application::createSolution(const std::string& filePath)
    {
        m_solution = std::shared_ptr<Solution>(new Solution());
        m_solution->save(filePath);

        return m_solution;
    }

};