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
    class Visitor;
};

namespace iris {

    class Solution
    {

    public:

        Solution();
        ~Solution();

        const std::string getFilePath() const { return m_filePath; }
        const std::string& getWorkingDirectory() const { return m_workingDirectory; }

        std::shared_ptr<Project> addProject(const std::string& filePath);
        bool removeProject(const std::string& filePath);

        bool verify();
        bool build(JSObject* context);

        bool accept(Visitor& visitor);

        bool load(const std::string& filePath);
        bool save(const std::string& filePath);

    private:

        std::string m_filePath;
        std::string m_workingDirectory;

        std::map<std::string, std::shared_ptr<Project>> m_projects;

    };

};