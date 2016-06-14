#pragma once

#include "../interface.hpp"
#include "task.hpp"

namespace iris {
    class Publish;

    namespace dom {
        class Document;
    }
};

namespace iris {

    class Project
        : public Task
    {

    public:

        Project(JSContext* context);
        ~Project();

        const std::string& getProjectPath() const { return m_projectPath; }
        const std::string& getIntermediatePath() const { return m_intermediatePath; }

        bool parse(const std::string& filePath);

        bool load(TiXmlElement* element, uint32_t version);
        void save(TiXmlElement* element, uint32_t version);

    private:

        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        JSContext* m_context;
        std::string m_filePath;
        std::string m_projectPath;
        std::string m_intermediatePath;
        std::shared_ptr<Publish> m_publish;
        std::shared_ptr<dom::Document> m_document;

    };

};