#pragma once

#include "../interface.hpp"

namespace iris {
    class Project;
    class Publish;
    class Solution;

    namespace dom {
        class Document;
    }
};

namespace iris {

    class Visitor
    {

    public:

        virtual ~Visitor() { }

        virtual bool visitEnter(const Solution& solution) { return true; }
        virtual bool visitLeave(const Solution& solution) { return true; }

        virtual bool visitEnter(const Project& project) { return true; }
        virtual bool visitLeave(const Project& project) { return true; }

        virtual bool visitEnter(const Publish& publish) { return true; }
        virtual bool visitLeave(const Publish& publish) { return true; }

        virtual bool visitEnter(const dom::Document& document) { return true; }
        virtual bool visitLeave(const dom::Document& document) { return true; }

    };

};