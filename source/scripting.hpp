/*
    Copyright (c) 2016 Bigpoint GmbH

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

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