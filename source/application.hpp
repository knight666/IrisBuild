#pragma once

#include "interface.hpp"

namespace iris {
    class Solution;
};

namespace iris {

    class Application
    {

    public:

        static Application& get();

        static void create();
        static void destroy();

        std::shared_ptr<Solution> getSolution() const { return m_solution; }

        std::shared_ptr<Solution> createSolution(const std::string& filePath);
        std::shared_ptr<Solution> loadSolution(const std::string& filePath);

    private:

        Application();
        ~Application();

        static Application* s_instance;

        std::shared_ptr<Solution> m_solution;

    };

};