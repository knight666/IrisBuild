#pragma once

#include "visitor.hpp"

namespace iris {

    class TreeVisitor
        : public Visitor
    {

    public:

        TreeVisitor();
        ~TreeVisitor();

        const std::string& getSerialized() const { return m_serialized; }

        virtual bool visitEnter(Solution& solution) override;
        virtual bool visitLeave(Solution& solution) override;

        virtual bool visitEnter(Project& project) override;

    private:

        TiXmlDocument m_document;
        TiXmlElement* m_solutionElement;

        std::string m_serialized;

    };

};