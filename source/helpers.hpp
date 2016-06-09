#pragma once

#include "interface.hpp"

namespace iris {
namespace helpers {

    std::string utf8(const std::wstring& value);
    std::wstring wide(const std::string& value);

    bool valueToString(JSContext& context, jsval& input, std::string& output);

    bool stringToValue(JSContext& context, const std::string& input, jsval& target);

    bool createDirectory(const std::string& path);
    bool fileExists(const std::string& path);
    std::string absolutePath(const std::string& path);

    std::string readElementText(TiXmlElement* parent, const char* name);
    std::string readAttributeText(TiXmlElement* owner, const char* name);

};
};