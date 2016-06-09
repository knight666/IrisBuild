#include "helpers.hpp"

#include "logging/logger.hpp"

namespace iris {
namespace helpers {

    std::string utf8(const std::wstring& value)
    {
        std::string converted;

        int32_t errors;

        size_t size_in_bytes = widetoutf8(value.c_str(), value.size() * UTF8_WCHAR_SIZE, nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return converted;
        }

        converted.resize(size_in_bytes);
        widetoutf8(value.c_str(), value.size() * UTF8_WCHAR_SIZE, &converted[0], size_in_bytes, nullptr);

        return converted;
    }

    std::wstring wide(const std::string& value)
    {
        std::wstring converted;

        int32_t errors;

        size_t size_in_bytes = utf8towide(value.c_str(), value.size(), nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return converted;
        }

        converted.resize(size_in_bytes / UTF8_WCHAR_SIZE);

        utf8towide(value.c_str(), value.size(), &converted[0], size_in_bytes, nullptr);

        return converted;
    }

    bool valueToString(JSContext& context, jsval& input, std::string& output)
    {
        unsigned int input_wide_length = 0;
        unsigned short* input_wide = JS_ValueToString(&context, input, &input_wide_length);

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
            return false;;
        }

        output.resize(size_in_bytes);
        widetoutf8(input_wide, input_wide_length * UTF8_WCHAR_SIZE, &output[0], size_in_bytes, nullptr);

        return true;
    }

    bool stringToValue(JSContext& context, const std::string& input, jsval& target)
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

        return (JS_StringToValue(&context, &converted[0], (uint32_t)(size_in_bytes / UTF8_WCHAR_SIZE), &target) == JS_TRUE);
    }

    bool createDirectory(const std::string& path)
    {
        std::wstring wide_path = wide(path);

        return ::CreateDirectoryW(wide_path.c_str(), nullptr) == TRUE;
    }

    bool fileExists(const std::string& path)
    {
        std::wstring wide_path = wide(path);

        WIN32_FIND_DATAW file_data = { 0 };
        HANDLE handle = ::FindFirstFileW(wide_path.c_str(), &file_data);
        bool found = handle != INVALID_HANDLE_VALUE;
        ::FindClose(handle);

        return found;
    }

    std::string absolutePath(const std::string& path)
    {
        std::wstring wide_path = wide(path);

        wchar_t buffer[_MAX_PATH + 1] = { 0 };
        ::GetFullPathNameW(wide_path.c_str(), _MAX_PATH, buffer, nullptr);

        return utf8(buffer);
    }

    std::string readElementText(TiXmlElement* parent, const char* name)
    {
        TiXmlElement* element = parent->FirstChildElement(name);
        if (element == nullptr)
        {
            Logger::get().write("ERROR! Missing \"%s\" element under \"%s\".", name, parent->Value());

            return "";
        }

        const char* text = element->GetText();

        return (text != nullptr) ? std::string(text) : "";
    }

    std::string readAttributeText(TiXmlElement* owner, const char* name)
    {
        const char* value = owner->Attribute(name);
        return (value != nullptr) ? std::string(value) : "";
    }

};
};