#pragma once

#include "../main.hpp"

namespace iris {
    class DependencyGraph;
};

namespace iris {

    class Task
    {

    public:

        Task();
        virtual ~Task();

        void reset();
        bool check();
        void update(DependencyGraph& graph);
        bool build();

        virtual std::string getTaskIntermediatePath() const = 0;
        virtual std::string getTaskSourcePath() const = 0;
        virtual std::string getTaskCommand() const = 0;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const = 0;

    protected:

        virtual bool onTaskBuild() = 0;

    private:

        bool m_cacheSet;
        bool m_cacheResult;
        std::string m_cacheCommand;

    };

};