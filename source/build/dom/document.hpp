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

#include "../../main.hpp"
#include "../task.hpp"

namespace iris {
    class Project;
    class Visitor;
};

namespace iris {
namespace dom {

    class Document
        : public Task
    {

    public:

        Document(Project& project);
        ~Document();

        Project& getProject() const { return m_project; }

        bool accept(Visitor& visitor);

        bool load(const std::string& filePath);

    private:

        virtual bool onTaskBuild(JSObject* context) override;
        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        Project& m_project;
        std::string m_filePath;
        std::shared_ptr<TiXmlDocument> m_document;

        std::vector<std::shared_ptr<Task>> m_dependencies;

    };

};
};