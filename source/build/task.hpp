#pragma once

#include "../interface.hpp"

namespace iris {

    class Task
    {

    public:

        Task();
        virtual ~Task();

        void reset();
        bool check();
        void update();

    protected:

        virtual std::string getTaskIntermediatePath() const = 0;
        virtual std::string getTaskSourcePath() const = 0;
        virtual std::string getTaskCommand() const = 0;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const = 0;

    private:

        bool m_cacheSet;
        bool m_cacheResult;
        std::string m_cacheCommand;

    };

};