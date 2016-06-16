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
    template<typename ValueType>
    bool fromJsfl(JSContext* context, const jsval& input, ValueType& target);

    template<>
    inline bool fromJsfl(JSContext* context, const jsval& input, std::string& target)
    {
        unsigned int input_wide_length = 0;
        unsigned short* input_wide = JS_ValueToString(context, input, &input_wide_length);

        if (input_wide == nullptr ||
            input_wide_length == 0)
        {
            return false;
        }

        int32_t errors = 0;

        size_t size_in_bytes = widetoutf8(input_wide, input_wide_length * UTF8_WCHAR_SIZE, nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return false;
        }

        target.resize(size_in_bytes);
        widetoutf8(input_wide, input_wide_length * UTF8_WCHAR_SIZE, &target[0], size_in_bytes, nullptr);

        return true;
    }

    template<>
    inline bool fromJsfl(JSContext* context, const jsval& input, double& target)
    {
        return JS_ValueToDouble(context, input, &target) == JS_TRUE;
    }

    template<typename ValueType>
    bool toJsfl(JSContext* context, const ValueType& input, jsval& target);

    template<>
    inline bool toJsfl(JSContext* context, const std::string& input, jsval& target)
    {
        int32_t errors = 0;

        size_t size_in_bytes = utf8towide(input.c_str(), input.size(), nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return false;
        }

        std::wstring converted;
        converted.resize(size_in_bytes / UTF8_WCHAR_SIZE);

        utf8towide(input.c_str(), input.size(), &converted[0], size_in_bytes, nullptr);

        return (JS_StringToValue(context, &converted[0], (uint32_t)(size_in_bytes / UTF8_WCHAR_SIZE), &target) == JS_TRUE);
    }

    template<>
    inline bool toJsfl(JSContext* context, const bool& input, jsval& target)
    {
        return toJsfl<std::string>(context, std::string(input ? "true" : "false"), target);
    }

    template<>
    inline bool toJsfl(JSContext* context, const double& input, jsval& target)
    {
        return JS_DoubleToValue(context, input, &target) == JS_TRUE;
    }

    // OS
    bool createDirectory(const std::string& path);
    bool fileExists(const std::string& path);
    std::string fileLastModifiedTime(const std::string& path);
    std::string absolutePath(const std::string& path);
    std::string relativePath(const std::string& pathFrom, const std::string& pathTo);
    std::string uriToAbsolute(const std::string& uri);

    // XML
    std::string readElementText(TiXmlElement* parent, const char* name);
    std::string readAttributeText(TiXmlElement* owner, const char* name);

};
};