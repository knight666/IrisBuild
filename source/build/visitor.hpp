#pragma once

#include "../main.hpp"

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

        virtual bool visitEnter(Solution& solution) { return true; }
        virtual bool visitLeave(Solution& solution) { return true; }

        virtual bool visitEnter(Project& project) { return true; }
        virtual bool visitLeave(Project& project) { return true; }

        virtual bool visitEnter(Publish& publish) { return true; }
        virtual bool visitLeave(Publish& publish) { return true; }

        virtual bool visitEnter(dom::Document& document) { return true; }
        virtual bool visitLeave(dom::Document& document) { return true; }

    };

};