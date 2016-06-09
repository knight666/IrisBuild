#include "publish.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"

namespace iris {

    Publish::Publish(std::shared_ptr<Logger> logger)
        : m_logger(logger)
    {
    }

    Publish::~Publish()
    {
    }

    bool Publish::load(const std::string& filePath)
    {
        m_logger->write("Loading publish settings at \"%s\".", filePath.c_str());
        if (!helpers::fileExists(filePath))
        {
            m_logger->write("ERROR! Failed to load file.");

            return false;
        }

        return true;
    }

};