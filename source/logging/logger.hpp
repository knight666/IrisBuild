#pragma once

#include "../interface.hpp"

namespace iris {

    class Logger
    {

    public:

        static Logger& get();

        static void create();
        static void destroy();

        void setFilePath(const std::string& filePath);

        void write(const char* message, ...);

    private:

        Logger();
        ~Logger();

        static Logger* s_instance;

        std::string m_filePath;
        std::ofstream m_file;

    };

};