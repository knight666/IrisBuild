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

#include "logger.hpp"

namespace iris {

    Logger::Logger()
        : m_levelMaximum(Level::Information)
    {
    }

    Logger::~Logger()
    {
    }

    Logger* Logger::s_instance = nullptr;

    Logger& Logger::get()
    {
        return *s_instance;
    }

    void Logger::create()
    {
        s_instance = new Logger();
    }

    void Logger::destroy()
    {
        delete s_instance;
        s_instance = nullptr;
    }

    void Logger::setMaximumLevel(Level level)
    {
        m_levelMaximum = level;

        IRIS_LOG_ERROR("setMaximumLevel %d", level);
    }

    void Logger::setFilePath(const std::string& filePath)
    {
        m_filePath = filePath;

        m_file.open(m_filePath.c_str(), std::ios::out | std::ios::trunc);
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    void Logger::write(Level level, const char* filepath, int line, const char* message, ...)
    {
        if (level > m_levelMaximum)
        {
            return;
        }

        m_file.open(m_filePath.c_str(), std::ios::out | std::ios::app);
        if (!m_file.is_open())
        {
            return;
        }

        static const char* LevelStrings[] = {
            "ERROR",
            "WARNING",
            "INFO",
            "TRACE",
            "INSANE"
        };

        if (level <= Level::Warning)
        {
            const char* path_last_slash = strrchr(filepath, '\\');
            const char* filename = (path_last_slash != nullptr) ? (path_last_slash + 1) : filepath;

            m_file << "(" << filename << ":" << line << ") ";
        }

        time_t current_time = time(0);
        struct tm* now = localtime(&current_time);

        char timestamp[32] = { 0 };
        sprintf_s(timestamp, 31, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);

        m_file << "[" << LevelStrings[(size_t)level] << "] [" << timestamp << "] ";
        
        va_list args;
        va_start(args, message);
        char buffer[1024] = { 0 };
        vsprintf_s(buffer, message, args);
        va_end(args);

        m_file << buffer << std::endl;

        m_file.close();
    }

};