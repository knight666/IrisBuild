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
#include "task.hpp"

namespace iris {
    class Publish;
    class Solution;
    class Visitor;

    namespace dom {
        class Document;
    }
};

namespace iris {

    class Project
        : public Task
    {

    public:

        Project(Solution& solution);
        ~Project();

        const std::string& getFilePath() const { return m_filePath; }
        const std::string& getProjectPath() const { return m_projectPath; }
        const std::string& getIntermediatePath() const { return m_intermediatePath; }

        bool parse(const std::string& filePath);

        bool accept(Visitor& visitor);

        bool load(TiXmlElement* element, uint32_t version);
        bool save(TiXmlElement* element, uint32_t version);

    private:

        virtual bool onTaskBuild(JSObject* context) override;
        virtual std::string getTaskIntermediatePath() const override;
        virtual std::string getTaskSourcePath() const override;
        virtual std::string getTaskCommand() const override;
        virtual std::vector<std::shared_ptr<Task>> getTaskDependencies() const override;

        Solution& m_solution;

        std::string m_filePath;
        std::string m_projectPath;
        std::string m_intermediatePath;
        std::shared_ptr<Publish> m_publish;
        std::shared_ptr<dom::Document> m_document;

    };

};