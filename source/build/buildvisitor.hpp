#pragma once

#include "visitor.hpp"

namespace iris {

    class BuildVisitor
        : public Visitor
    {

    public:

        BuildVisitor();
        ~BuildVisitor();

        const std::vector<Project*>& getProjects() const { return m_projects; }

        virtual bool visitEnter(Solution& solution) override;

        virtual bool visitEnter(Project& project) override;

    private:

        std::vector<Project*> m_projects;

    };

};