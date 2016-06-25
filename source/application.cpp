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

    bool Application::createSolution(const std::string& filePath)
    {
        m_solution = std::shared_ptr<Solution>(new Solution());
        return m_solution->save(filePath);
    }

};