#pragma once

#include "../../interface.hpp"
#include "../task.hpp"

namespace iris {
    class Project;

    namespace dom {
        class BitmapItem;
    };
};

namespace iris {
namespace dom {

    class Document
        : public Task
    {

    public:

        Document(Project& project);
        ~Document();

        bool load(const std::string& filePath);

    private:

        bool parseMedia(TiXmlElement* element);

        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        Project& m_project;
        std::string m_filePath;
        std::shared_ptr<TiXmlDocument> m_document;

        std::vector<std::shared_ptr<BitmapItem>> m_bitmaps;

    };

};
};