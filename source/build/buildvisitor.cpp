#include "buildvisitor.hpp"

#include "project.hpp"
#include "solution.hpp"

namespace iris {

    BuildVisitor::BuildVisitor()
    {

    }

    BuildVisitor::~BuildVisitor()
    {

    }

    bool BuildVisitor::visitEnter(Solution& solution)
    {
        m_projects.clear();

        return true;
    }

    bool BuildVisitor::visitEnter(Project& project)
    {
        if (!project.check())
        {
            m_projects.push_back(&project);
        }

        return true;
    }

};