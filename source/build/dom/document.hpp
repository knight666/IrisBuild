#pragma once

#include "../../interface.hpp"

namespace iris {

    class Logger;
    class Project;

};

namespace iris {
namespace dom {

    class Document
    {

    public:

        Document(Project& project, std::shared_ptr<Logger> logger);
        ~Document();

        bool load(const std::string& filePath);

    private:

        bool parseMedia(TiXmlElement& element);

        Project& m_project;
        std::shared_ptr<Logger> m_logger;
        std::shared_ptr<TiXmlDocument> m_document;

    };

};
};