#include "logger.hpp"

namespace iris {

    Logger::Logger(const std::string& filePath)
    {
        m_filePath = filePath;

        m_file.open(m_filePath.c_str(), std::ios::out | std::ios::trunc);
        if (m_file.is_open())
        {
            m_file.close();
        }
    }


    Logger::~Logger()
    {
    }

    void Logger::write(const char* message, ...)
    {
        m_file.open(m_filePath.c_str(), std::ios::out | std::ios::app);
        if (!m_file.is_open())
        {
            return;
        }

        time_t current_time = time(0);
        struct tm* now = localtime(&current_time);

        char timestamp[32] = { 0 };
        sprintf_s(timestamp, 31, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);

        va_list args;
        va_start(args, message);
        char buffer[1024] = { 0 };
        vsprintf_s(buffer, message, args);
        va_end(args);

        m_file << "[" << timestamp << "] " << buffer << std::endl;

        m_file.close();
    }

};