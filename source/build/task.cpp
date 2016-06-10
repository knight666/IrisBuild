#include "task.hpp"

#include "../logging/logger.hpp"
#include "../helpers.hpp"

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

        // Check timestamps on source and intermediate file

        std::string intermediate = getTaskIntermediatePath();
        std::string intermediate_time = helpers::fileLastModifiedTime(intermediate);

        std::string source = getTaskSourcePath();
        std::string source_time = helpers::fileLastModifiedTime(source);

        Logger::get().write("intermediatePath: %s", intermediate.c_str());
        Logger::get().write("intermediateTime: %s", intermediate_time.c_str());
        Logger::get().write("sourcePath: %s", source.c_str());
        Logger::get().write("sourceTime: %s", source_time.c_str());
        Logger::get().write("command: %s", command.str().c_str());

        return m_cacheResult;
    }

};