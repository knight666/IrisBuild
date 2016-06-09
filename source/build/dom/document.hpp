#pragma once

#include "../../interface.hpp"

namespace iris {

    class Project;

};

namespace iris {
namespace dom {

    class Document
    {

    public:

        Document(Project& project);
        ~Document();

        bool load(const std::string& filePath);

    private:

        bool parseMedia(TiXmlElement& element);

        Project& m_project;
        std::shared_ptr<TiXmlDocument> m_document;

    };

};
};