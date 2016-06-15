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

    bool TreeVisitor::visitEnter(const Solution& solution)
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

    bool TreeVisitor::visitLeave(const Solution& solution)
    {
        TiXmlPrinter printer;
        printer.SetIndent(nullptr);
        printer.SetLineBreak(nullptr);

        m_document.Accept(&printer);

        m_serialized = printer.CStr();

        return true;
    }

    bool TreeVisitor::visitEnter(const Project& project)
    {
        TiXmlElement* project_element = new TiXmlElement("node");

        char filename[_MAX_FNAME] = { 0 };
        _splitpath(project.getFilePath().c_str(), nullptr, nullptr, filename, nullptr);

        project_element->SetAttribute("label", filename);
        m_solutionElement->LinkEndChild(project_element);

        return true;
    }

};