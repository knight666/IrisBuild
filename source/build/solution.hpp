#pragma once

#include "../main.hpp"

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

        std::shared_ptr<Project> addProject(const std::string& filePath);
        bool removeProject(const std::string& filePath);

        bool verify();
        bool build(JSObject* context);

        bool accept(Visitor& visitor);

        bool load(const std::string& filePath);
        bool save(const std::string& filePath);

    private:

        std::string m_filePath;
        std::string m_workingDirectory;

        std::map<std::string, std::shared_ptr<Project>> m_projects;

    };

};