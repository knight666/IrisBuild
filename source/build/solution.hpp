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

        static Solution& get();

        static void create();
        static void destroy();

        const std::string getFilePath() const { return m_filePath; }
        const std::string& getWorkingDirectory() const { return m_workingDirectory; }

        std::string getSerializedDataProvider() const;

        bool accept(Visitor& visitor) const;

        std::shared_ptr<Project> getCurrentProject() const;
        void addProject(std::shared_ptr<Project> project);

        bool load(const std::string& filePath);
        void save(const std::string& filePath);

    private:

        Solution();
        ~Solution();

        static Solution* s_instance;

        std::string m_filePath;
        std::string m_workingDirectory;

        std::vector<std::shared_ptr<Project>> m_projects;

    };

};