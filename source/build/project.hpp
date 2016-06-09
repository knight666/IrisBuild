#pragma once

#include "../interface.hpp"

namespace iris {

    class Logger;
    class Publish;

    class Project
    {

    public:

        Project(JSContext* context);
        ~Project();

        const std::string& getIntermediatePath() const { return m_intermediatePath; }

        bool load(const std::string& filePath);

    private:

        JSContext* m_context;
        std::string m_projectPath;
        std::string m_intermediatePath;
        std::shared_ptr<Logger> m_logger;
        std::shared_ptr<Publish> m_publish;

    };

};