#pragma once

#include "../interface.hpp"

namespace iris {

    class Logger;

    class Publish
    {

    public:

        Publish(std::shared_ptr<Logger> logger);
        ~Publish();

        bool load(const std::string& filePath);

    private:

        std::shared_ptr<Logger> m_logger;

    };

};