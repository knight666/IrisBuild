#include "task.hpp"

#include "../logging/logger.hpp"

namespace iris {

    Task::Task()
        : m_cacheSet(false)
        , m_cacheResult(false)
    {
    }

    Task::~Task()
    {
    }

    void Task::reset()
    {
        m_cacheSet = false;
        m_cacheResult = false;

        std::vector<std::shared_ptr<Task>> dependencies = getTaskDependencies();
        for (std::shared_ptr<Task> task : dependencies)
        {
            task->reset();
        }
    }

    bool Task::check()
    {
        if (m_cacheSet)
        {
            return m_cacheResult;
        }

        m_cacheResult = true;
        m_cacheSet = true;

        // Build task command output

        std::stringstream command;

        command << getTaskCommand() << std::endl;

        std::vector<std::shared_ptr<Task>> dependencies = getTaskDependencies();
        for (std::shared_ptr<Task> task : dependencies)
        {
            m_cacheResult = m_cacheResult && task->check();
            command << task->getTaskIntermediatePath() << std::endl;
        }

        Logger::get().write("taskIntermediatePath: %s", getTaskIntermediatePath().c_str());
        Logger::get().write("sourcePath: %s", getTaskSourcePath().c_str());
        Logger::get().write(command.str().c_str());

        return m_cacheResult;
    }

};