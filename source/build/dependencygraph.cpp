#include "dependencygraph.hpp"

#include "../logging/logger.hpp"
#include "task.hpp"

namespace iris {

    DependencyGraph::DependencyGraph()
    {
    }

    DependencyGraph::~DependencyGraph()
    {
    }

    std::vector<DependencyGraph::Dependency> DependencyGraph::getFlattenedList() const
    {
        std::vector<Dependency> tasks;

        for (std::pair<std::string, Dependency> it : m_dependencies)
        {
            tasks.push_back(it.second);
        }

        std::sort(tasks.begin(), tasks.end());

        IRIS_LOG_TRACE("dependencies:");

        for (Dependency& dependency : tasks)
        {
            IRIS_LOG_TRACE("\t- %s (%d)", dependency.task->getTaskSourcePath().c_str(), dependency.count);
        }

        return tasks;
    }

    void DependencyGraph::addDependency(Task& task)
    {
        std::map<std::string, Dependency>::iterator found = m_dependencies.find(task.getTaskSourcePath());
        if (found != m_dependencies.end())
        {
            found->second.count++;
        }
        else
        {
            Dependency dependency;
            dependency.task = &task;
            dependency.count = 1;

            m_dependencies.insert(std::make_pair(task.getTaskSourcePath(), dependency));
        }
    }

};