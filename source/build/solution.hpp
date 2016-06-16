#pragma once

#include "../interface.hpp"

namespace iris {
    class Project;
    class Visitor;
};

namespace iris {

    class Solution
    {

    public:

        Solution();
        ~Solution();

        const std::string getFilePath() const { return m_filePath; }
        const std::string& getWorkingDirectory() const { return m_workingDirectory; }

        bool verify();

        bool accept(Visitor& visitor);

        std::shared_ptr<Project> getCurrentProject() const;
        void addProject(std::shared_ptr<Project> project);

        bool load(const std::string& filePath);
        bool save(const std::string& filePath);

    private:

        std::string m_filePath;
        std::string m_workingDirectory;

        std::vector<std::shared_ptr<Project>> m_projects;

    };

};