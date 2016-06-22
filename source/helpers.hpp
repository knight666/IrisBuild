#pragma once

#include "main.hpp"

#define XML_FOR_EACH(_element, _name, _iterator) \
    for (TiXmlElement*  ##_iterator = (_element)->FirstChildElement(_name); \
        ##_iterator != nullptr; \
        ##_iterator = ##_iterator -> NextSiblingElement(_name))

namespace iris {
namespace helpers {

    // Strings
    std::string utf8(const std::wstring& text);
    std::vector<uint16_t> utf16(const std::string& text);
    std::wstring wide(const std::string& text);
    std::string casefold(const std::string& text);

    // OS
    bool createDirectory(const std::string& path);
    bool fileExists(const std::string& path);
    std::string fileLastModifiedTime(const std::string& path);
    std::string absolutePath(const std::string& path);
    std::string relativePath(const std::string& pathFrom, const std::string& pathTo);
    std::string uriToAbsolute(const std::string& uri);
    std::string absolutePathToUri(const std::string& path);

    // XML
    std::string readElementText(TiXmlElement* parent, const char* name);
    std::string readAttributeText(TiXmlElement* owner, const char* name);

};
};