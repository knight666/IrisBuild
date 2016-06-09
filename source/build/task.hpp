#pragma once

#include "../interface.hpp"

namespace iris {

    class Task
    {

    public:

        Task();
        virtual ~Task();

        void reset();
        bool check();

    protected:

        virtual std::string getName() const = 0;
        virtual std::string getSourceName() const = 0;
        virtual std::string getCommand() const = 0;
        virtual std::vector<std::shared_ptr<Task>> getDependencies() const = 0;

    private:

        bool m_cacheSet;
        bool m_cacheResult;

    };

};