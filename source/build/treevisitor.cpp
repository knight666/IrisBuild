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

#include "treevisitor.hpp"

#include "project.hpp"
#include "solution.hpp"

namespace iris {

    TreeVisitor::TreeVisitor()
        : m_solutionElement(nullptr)
    {
    }

    TreeVisitor::~TreeVisitor()
    {
    }

    bool TreeVisitor::visitEnter(Solution& solution)
    {
        m_document.Clear();
        m_solutionElement = nullptr;
        m_serialized.clear();

        TiXmlElement* root_element = new TiXmlElement("root");
        m_document.LinkEndChild(root_element);

        char filename[_MAX_FNAME] = { 0 };
        _splitpath(solution.getFilePath().c_str(), nullptr, nullptr, filename, nullptr);

        m_solutionElement = new TiXmlElement("node");
        m_solutionElement->SetAttribute("label", filename);
        root_element->LinkEndChild(m_solutionElement);

        return true;
    }

    bool TreeVisitor::visitLeave(Solution& solution)
    {
        TiXmlPrinter printer;
        printer.SetIndent(nullptr);
        printer.SetLineBreak(nullptr);

        m_document.Accept(&printer);

        m_serialized = printer.CStr();

        return true;
    }

    bool TreeVisitor::visitEnter(Project& project)
    {
        TiXmlElement* project_element = new TiXmlElement("node");

        char filename[_MAX_FNAME] = { 0 };
        _splitpath(project.getFilePath().c_str(), nullptr, nullptr, filename, nullptr);

        project_element->SetAttribute("label", filename);
        project_element->SetAttribute("icon", project.check() ? "iconClean" : "iconDirty");
        m_solutionElement->LinkEndChild(project_element);

        return true;
    }

};