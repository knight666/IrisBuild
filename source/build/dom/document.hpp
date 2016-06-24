#pragma once

#include "../../main.hpp"
#include "../task.hpp"

namespace iris {
    class Project;
    class Visitor;
};

namespace iris {
namespace dom {

    class Document
        : public Task
    {

    public:

        Document(Project& project);
        ~Document();

        Project& getProject() const { return m_project; }

        bool accept(Visitor& visitor);

        bool load(const std::string& filePath);

    private:

        virtual bool onTaskBuild() override;
        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        Project& m_project;
        std::string m_filePath;
        std::shared_ptr<TiXmlDocument> m_document;

        std::vector<std::shared_ptr<Task>> m_dependencies;

    };

};
};