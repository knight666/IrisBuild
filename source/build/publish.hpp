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

        bool findElement(TiXmlNode* parent, const char* name, TiXmlElement** target);

        std::shared_ptr<Logger> m_logger;
        std::shared_ptr<TiXmlDocument> m_document;

    };

};