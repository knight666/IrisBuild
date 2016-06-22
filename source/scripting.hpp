#pragma once

#include "main.hpp"

#define IRIS_JS_EVAL(_object, _script) \
    ::iris::Scripting::get().evaluate(_object, _script, __FILE__, __LINE__)

namespace iris {

    class Scripting
    {

    public:

        static Scripting& get();

        static void create();
        static void destroy();

        void setContext(JSContext* context);

        template<typename ValueType>
        bool fromJsfl(const jsval& input, ValueType& target);

        template<>
        inline bool fromJsfl(const jsval& input, std::string& target)
        {
            unsigned int input_wide_length = 0;
            unsigned short* input_wide = JS_ValueToString(m_context, input, &input_wide_length);

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
        inline bool fromJsfl(const jsval& input, double& target)
        {
            return JS_ValueToDouble(m_context, input, &target) == JS_TRUE;
        }

        template<typename ValueType>
        bool toJsfl(const ValueType& input, jsval& target);

        template<>
        inline bool toJsfl(const std::string& input, jsval& target)
        {
            int32_t errors = 0;

            size_t size_in_bytes = utf8toutf16(input.c_str(), input.size(), nullptr, 0, &errors);
            if (size_in_bytes == 0 ||
                errors != UTF8_ERR_NONE)
            {
                return false;
            }

            std::vector<utf16_t> converted;
            converted.resize(size_in_bytes / sizeof(utf16_t));

            utf8toutf16(input.c_str(), input.size(), &converted[0], size_in_bytes, nullptr);

            return (JS_StringToValue(m_context, &converted[0], (uint32_t)(size_in_bytes / sizeof(utf16_t)), &target) == JS_TRUE);
        }

        template<>
        inline bool toJsfl(const bool& input, jsval& target)
        {
            return toJsfl<std::string>(std::string(input ? "true" : "false"), target);
        }

        template<>
        inline bool toJsfl(const double& input, jsval& target)
        {
            return JS_DoubleToValue(m_context, input, &target) == JS_TRUE;
        }

        template<>
        inline bool toJsfl(const std::vector<std::string>& input, jsval& target)
        {
            // Allocate a string first, which prevents a crash in Flash.
            if (JS_StringToValue(m_context, L"0", 1, &target) != JS_TRUE)
            {
                return false;
            }

            std::vector<jsval> values;
            values.reserve(input.size());

            for (const std::string& text : input)
            {
                jsval converted;
                toJsfl(text, converted);
                values.push_back(converted);
            }

            JSObject* array = JS_NewArrayObject(m_context, (uint32_t)values.size(), &values[0]);
            if (array == nullptr)
            {
                return false;
            }

            target = JS_ObjectToValue(array);

            return true;
        }

        jsval evaluate(JSObject* object, const std::string& script, const char* filePath, uint32_t line);

    private:

        Scripting();
        ~Scripting();

        static Scripting* s_instance;

        JSContext* m_context;

    };

}