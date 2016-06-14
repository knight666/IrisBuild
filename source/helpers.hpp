#pragma once

#include "interface.hpp"

#define XML_FOR_EACH(_element, _name, _iterator) \
    for (TiXmlElement*  ##_iterator = (_element)->FirstChildElement(_name); \
        ##_iterator != nullptr; \
        ##_iterator = ##_iterator -> NextSiblingElement(_name))

namespace iris {
namespace helpers {

    // Strings
    std::string utf8(const std::wstring& text);
    std::wstring wide(const std::string& text);
    std::string casefold(const std::string& text);

    // JSFL
    bool valueToString(JSContext& context, jsval& input, std::string& output);
    bool stringToValue(JSContext& context, const std::string& input, jsval& target);

    template<typename ValueType>
    ValueType fromJsfl(JSContext* context, jsval value);

    template<>
    inline std::string fromJsfl(JSContext* context, jsval value)
    {
        unsigned int value_width_length = 0;
        unsigned short* value_wide = JS_ValueToString(context, value, &value_width_length);

        if (value_wide == nullptr ||
            value_width_length == 0)
        {
            return std::string();
        }

        int32_t errors = 0;

        size_t size_in_bytes = widetoutf8(value_wide, value_width_length * UTF8_WCHAR_SIZE, nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return std::string();
        }

        std::string converted;
        converted.resize(size_in_bytes);
        widetoutf8(value_wide, value_width_length * UTF8_WCHAR_SIZE, &converted[0], size_in_bytes, nullptr);

        return converted;
    }

    template<typename ValueType>
    jsval toJsfl(JSContext* context, const ValueType& value);

    template<>
    inline jsval toJsfl(JSContext* context, const std::string& value)
    {
        int32_t errors = 0;

        size_t size_in_bytes = utf8towide(value.c_str(), value.size(), nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return (jsval)0;
        }

        std::wstring converted;
        converted.resize(size_in_bytes / UTF8_WCHAR_SIZE);

        utf8towide(value.c_str(), value.size(), &converted[0], size_in_bytes, nullptr);

        jsval result;
        JS_StringToValue(context, &converted[0], (uint32_t)(size_in_bytes / UTF8_WCHAR_SIZE), &result);

        return result;
    }

    template<>
    inline jsval toJsfl(JSContext* context, const bool& value)
    {
        return toJsfl<std::string>(context, std::string(value ? "true" : "false"));
    }

    // OS
    bool createDirectory(const std::string& path);
    bool fileExists(const std::string& path);
    std::string fileLastModifiedTime(const std::string& path);
    std::string absolutePath(const std::string& path);
    std::string uriToAbsolute(const std::string& uri);

    // XML
    std::string readElementText(TiXmlElement* parent, const char* name);
    std::string readAttributeText(TiXmlElement* owner, const char* name);

};
};