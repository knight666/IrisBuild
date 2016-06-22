#pragma once

#include "visitor.hpp"

namespace iris {

    class BuildVisitor
        : public Visitor
    {

    public:

        BuildVisitor(JSObject* context);
        ~BuildVisitor();

        const std::vector<Project*>& getProjects() const { return m_projects; }

        virtual bool visitEnter(Solution& solution) override;
        virtual bool visitLeave(Solution& solution) override;

        virtual bool visitEnter(Project& project) override;

    private:

        JSObject* m_context;
        std::vector<Project*> m_projects;

    };

};