#pragma once

#include "../interface.hpp"

namespace iris {

    class Logger
    {

    public:

        Logger(const std::string& filePath);
        ~Logger();

        void write(const char* message, ...);

    private:

        std::string m_filePath;
        std::ofstream m_file;

    };

};