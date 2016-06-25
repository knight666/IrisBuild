/*
    Copyright (c) 2016 Bigpoint GmbH

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

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