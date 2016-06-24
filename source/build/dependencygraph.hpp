#pragma once

#include "../main.hpp"

namespace iris {
    class Task;
};

namespace iris {

    class DependencyGraph
    {

    public:

        struct Dependency
        {
            Task* task;
            size_t count;

            bool operator < (const Dependency& other) const
            {
                return count < other.count;
            }
        };

        DependencyGraph();
        ~DependencyGraph();

        std::vector<Dependency> getFlattenedList() const;

        void addDependency(Task& task);

    private:

        std::map<std::string, Dependency> m_dependencies;

    };

};