/*
    Copyright (c) 2016 Bigpoint GmbH

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

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