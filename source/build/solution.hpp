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

    private:

        static Solution* s_instance;

        Solution();
        ~Solution();

        std::vector<std::shared_ptr<Project>> m_projects;

    };

};