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
        Logger::get().write("sourcePath: %s", source.c_str());

        std::string intermediate = getTaskIntermediatePath();
        Logger::get().write("intermediatePath: %s", intermediate.c_str());

        // Build task command output

        std::stringstream command_stream;

        command_stream << helpers::casefold(getTaskCommand()) << std::endl;

        std::vector<std::shared_ptr<Task>> dependencies = getTaskDependencies();
        for (std::shared_ptr<Task> task : dependencies)
        {
            bool task_check = task->check();
            m_cacheResult = m_cacheResult && task_check;
            if (!task_check)
            {
                Logger::get().write("Dependency \"%s\" was out-of-date.", task->getTaskSourcePath().c_str());
            }

            command_stream << helpers::casefold(task->getTaskIntermediatePath()) << std::endl;
        }

        std::string command = command_stream.str();

        // Check timestamps on source and intermediate file

        if (m_cacheResult)
        {
            std::string source_time = helpers::fileLastModifiedTime(source);
            Logger::get().write("sourceTime: %s", source_time.c_str());

            std::string intermediate_time = helpers::fileLastModifiedTime(intermediate);
            Logger::get().write("intermediateTime: %s", intermediate_time.c_str());

            m_cacheResult = source_time <= intermediate_time;
        }

        // Check previously stored command output with current command output

        if (m_cacheResult)
        {
            std::string command_previous;

            if (helpers::fileExists(intermediate))
            {
                std::ifstream file(intermediate, std::ios::in | std::ios::binary);
                std::stringstream file_stream;
                file_stream << file.rdbuf();
                file.close();

                command_previous = file_stream.str();
            }

            Logger::get().write("command: %s", command.c_str());
            Logger::get().write("commandPrevious: %s", command_previous.c_str());

            m_cacheResult = command == command_previous;
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

        Logger::get().write("%s: %s", source.c_str(), m_cacheResult ? "up-to-date" : "OUT-OF-DATE");

        return m_cacheResult;
    }

};