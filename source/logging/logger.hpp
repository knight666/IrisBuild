#pragma once

#include "../interface.hpp"

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