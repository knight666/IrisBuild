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

#pragma once

#include "../main.hpp"

#define IRIS_LOG_ERROR(_message, ...)   ::iris::Logger::get().write(::iris::Logger::Level::Error, __FILE__, __LINE__, _message, __VA_ARGS__)
#define IRIS_LOG_WARN(_message, ...)    ::iris::Logger::get().write(::iris::Logger::Level::Warning, __FILE__, __LINE__, _message, __VA_ARGS__)
#define IRIS_LOG_INFO(_message, ...)    ::iris::Logger::get().write(::iris::Logger::Level::Information, __FILE__, __LINE__, _message, __VA_ARGS__)
#define IRIS_LOG_TRACE(_message, ...)   ::iris::Logger::get().write(::iris::Logger::Level::Trace, __FILE__, __LINE__, _message, __VA_ARGS__)
#define IRIS_LOG_INSANE(_message, ...)  ::iris::Logger::get().write(::iris::Logger::Level::Insane, __FILE__, __LINE__, _message, __VA_ARGS__)

namespace iris {

    class Logger
    {

    public:

        enum class Level
        {
            Error,
            Warning,
            Information,
            Trace,
            Insane
        };

        static Logger& get();

        static void create();
        static void destroy();

        Level getMaximumLevel() const { return m_levelMaximum; }
        void setMaximumLevel(Level level);

        void setFilePath(const std::string& filePath);

        void write(Level level, const char* filepath, int line, const char* message, ...);

    private:

        Logger();
        ~Logger();

        static Logger* s_instance;

        Level m_levelMaximum;
        std::string m_filePath;
        std::ofstream m_file;

    };

};