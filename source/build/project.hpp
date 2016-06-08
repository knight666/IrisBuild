#pragma once

#include "../interface.hpp"

namespace iris {

    class Project
    {

    public:

        Project(JSContext* context);
        ~Project();

        const std::string& getIntermediatePath() const { return m_intermediatePath; }

        bool load(const std::string& filePath);

    private:

        JSContext* m_context;
        std::string m_filePath;
        std::string m_intermediatePath;

    };

};