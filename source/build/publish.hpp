#pragma once

#include "../interface.hpp"

namespace iris {
    class Project;
    class Visitor;
};

namespace iris {

    class Publish
    {

    public:

        Publish(Project& project);
        ~Publish();

        bool accept(Visitor& visitor) const;

        bool load(const std::string& filePath);

    private:

        Project& m_project;
        std::shared_ptr<TiXmlDocument> m_document;

        bool m_enabled;
        std::string m_publishPath;
        std::string m_actionScriptVersion;
        std::string m_packagePaths;
        std::string m_constants;
        std::string m_documentClass;

    };

};