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

#include "symbol.hpp"

#include "../../logging/logger.hpp"
#include "../../helpers.hpp"
#include "../project.hpp"
#include "document.hpp"

namespace iris {
namespace dom {

    Symbol::Symbol(Document& document)
        : m_document(document)
        , m_element(nullptr)
    {
    }

    Symbol::~Symbol()
    {
    }

    bool Symbol::parse(TiXmlElement* element)
    {
        m_href = helpers::readAttributeText(element, "href");

        m_element = element;

        return true;
    }

    bool Symbol::onTaskBuild(JSObject* context)
    {
        return true;
    }

    std::string Symbol::getTaskIntermediatePath() const
    {
        char directory[_MAX_DIR] = { 0 };
        char filename[_MAX_FNAME] = { 0 };
        _splitpath(m_href.c_str(), nullptr, directory, filename, nullptr);

        return helpers::absolutePath(m_document.getProject().getIntermediatePath() + "\\" + directory + "\\" + filename + ".tlog");
    }

    std::string Symbol::getTaskSourcePath() const
    {
        return helpers::absolutePath(m_document.getProject().getProjectPath() + m_href);
    }

    std::string Symbol::getTaskCommand() const
    {
        std::string result = helpers::readAttributeText(m_element, "href");
        result += " " + helpers::readAttributeText(m_element, "itemID");
        result += " " + helpers::readAttributeText(m_element, "lastModified");

        return result;
    }

    std::vector<std::shared_ptr<Task>> Symbol::getTaskDependencies() const
    {
        std::vector<std::shared_ptr<Task>> dependencies;

        return dependencies;
    }

};
};