#pragma once

#include "../../main.hpp"
#include "../task.hpp"

namespace iris {
    namespace dom {
        class Document;
    };
};

namespace iris {
namespace dom {

    class BitmapItem
        : public Task
    {

    public:

        BitmapItem(Document& document);
        ~BitmapItem();

        bool parse(TiXmlElement* element);

    private:

        virtual bool onTaskBuild(JSObject* context) override;
        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        Document& m_document;
        TiXmlElement* m_element;

        std::string m_name;
        std::string m_linkageIdentifier;
        std::string m_linkageURL;
        std::string m_sourceExternalFilepath;
        std::string m_href;

    };

};
};