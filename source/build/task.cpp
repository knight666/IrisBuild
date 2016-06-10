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

        std::string source = getTaskSourcePath();
        std::string source_time;
        IRIS_LOG_INSANE("sourcePath: %s", source.c_str());

        std::string intermediate = getTaskIntermediatePath();
        std::string intermediate_time;
        IRIS_LOG_INSANE("intermediatePath: %s", intermediate.c_str());

        // Build task command output

        std::stringstream command_stream;

        command_stream << helpers::casefold(getTaskCommand()) << std::endl;

        bool reason_timestamps = true;
        bool reason_command = true;
        std::vector<std::shared_ptr<Task>> reason_tasks_dirty;

        std::vector<std::shared_ptr<Task>> dependencies = getTaskDependencies();
        for (std::shared_ptr<Task> task : dependencies)
        {
            bool task_check = task->check();
            m_cacheResult = m_cacheResult && task_check;
            if (!task_check)
            {
                reason_tasks_dirty.push_back(task);
            }

            command_stream << helpers::casefold(task->getTaskIntermediatePath()) << std::endl;
        }

        std::string command = command_stream.str();
        std::string command_previous;

        // Check timestamps on source and intermediate file

        if (m_cacheResult)
        {
            source_time = helpers::fileLastModifiedTime(source);
            intermediate_time = helpers::fileLastModifiedTime(intermediate);

            m_cacheResult = reason_timestamps = source_time <= intermediate_time;
        }

        // Check previously stored command output with current command output

        if (m_cacheResult)
        {
            if (helpers::fileExists(intermediate))
            {
                std::ifstream file(intermediate, std::ios::in | std::ios::binary);
                std::stringstream file_stream;
                file_stream << file.rdbuf();
                file.close();

                command_previous = file_stream.str();
            }

            m_cacheResult = reason_command = command == command_previous;
        }

        IRIS_LOG_TRACE("%s: %s", m_cacheResult ? "up-to-date" : "OUT-OF-DATE", source.c_str());

        if (!m_cacheResult)
        {
            if (!reason_tasks_dirty.empty())
            {
                IRIS_LOG_TRACE("\t- dependencies:");

                for (std::shared_ptr<Task> task : reason_tasks_dirty)
                {
                    std::string source = task->getTaskSourcePath();
                    IRIS_LOG_TRACE("\t\t%s", source.c_str());
                }
            }

            if (!reason_timestamps)
            {
                IRIS_LOG_TRACE("\t- timestamps");
                IRIS_LOG_TRACE("\t\tsource:        %s", source_time.c_str());
                IRIS_LOG_TRACE("\t\tintermediate:  %s", intermediate_time.c_str());
            }

            if (!reason_command)
            {
                IRIS_LOG_TRACE("\t- command");
                IRIS_LOG_TRACE("\t\tsource:        %s", command.c_str());
                IRIS_LOG_TRACE("\t\tintermediate:  %s", command_previous.c_str());
            }
        }

        // Write intermediate file

        if (!m_cacheResult)
        {
            char drive[_MAX_DRIVE] = { 0 };
            char directory[_MAX_DIR] = { 0 };
            _splitpath(intermediate.c_str(), drive, directory, nullptr, nullptr);

            helpers::createDirectory(std::string(drive) + directory);

            std::ofstream file(intermediate, std::ios::out | std::ios::binary | std::ios::trunc);
            file << command;
            file.close();
        }

        return m_cacheResult;
    }

};