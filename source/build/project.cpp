#include "project.hpp"

namespace iris {

    Project::Project(JSContext* context)
        : m_context(context)
    {
    }

    Project::~Project()
    {
    }

    bool Project::load(const std::string& filePath)
    {
        m_filePath = filePath;

        m_intermediatePath = m_filePath;
        const size_t last_slash = m_intermediatePath.find_last_of('\\');
        if (last_slash != std::string::npos)
        {
            m_intermediatePath.erase(last_slash, m_intermediatePath.length() - last_slash);
        }

        return true;
    }

};