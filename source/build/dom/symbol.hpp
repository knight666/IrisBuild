#pragma once

#include "../../interface.hpp"
#include "../task.hpp"

namespace iris {
    namespace dom {
        class Document;
    };
};

namespace iris {
namespace dom {

    class Symbol
        : public Task
    {

    public:

        Symbol(Document& document);
        ~Symbol();

        bool parse(TiXmlElement* element);

    private:

        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        Document& m_document;
        TiXmlElement* m_element;

        std::string m_href;

    };

};
};