#pragma once

#include "../interface.hpp"

namespace iris {

    class Publish;

    namespace dom {

        class Document;

    }
};

namespace iris {

    class Project
    {

    public:

        Project(JSContext* context);
        ~Project();

        const std::string& getProjectPath() const { return m_projectPath; }
        const std::string& getIntermediatePath() const { return m_intermediatePath; }

        bool load(const std::string& filePath);

    private:

        JSContext* m_context;
        std::string m_projectPath;
        std::string m_intermediatePath;
        std::shared_ptr<Publish> m_publish;
        std::shared_ptr<dom::Document> m_document;

    };

};