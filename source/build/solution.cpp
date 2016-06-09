#include "solution.hpp"

namespace iris {

    Solution* Solution::s_instance = nullptr;

    Solution::Solution()
    {
    }

    Solution::~Solution()
    {
    }

    Solution& Solution::get()
    {
        return *s_instance;
    }

    void Solution::create()
    {
        s_instance = new Solution();
    }

    void Solution::destroy()
    {
        delete s_instance;
        s_instance = nullptr;
    }

    std::shared_ptr<Project> Solution::getCurrentProject() const
    {
        if (m_projects.size() == 0)
        {
            return nullptr;
        }

        return m_projects[m_projects.size() - 1];
    }

    void Solution::addProject(std::shared_ptr<Project> project)
    {
        m_projects.push_back(project);
    }

};