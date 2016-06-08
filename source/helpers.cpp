#include "helpers.hpp"

namespace iris {
namespace helpers {

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

};
};