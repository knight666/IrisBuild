#pragma once

#include "../interface.hpp"

namespace iris {

    class Project;

    class Solution
    {

    public:

        static Solution& get();

        static void create();
        static void destroy();

        std::shared_ptr<Project> getCurrentProject() const;
        void addProject(std::shared_ptr<Project> project);

        bool load(const std::string& filePath);
        void save(const std::string& filePath);

    private:

        Solution();
        ~Solution();

        static Solution* s_instance;

        std::vector<std::shared_ptr<Project>> m_projects;
        std::string m_workingDirectory;

    };

};