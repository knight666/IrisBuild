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

#include "scripting.hpp"

#include "logging/logger.hpp"
#include "helpers.hpp"

namespace iris {

    Scripting::Scripting()
        : m_context(nullptr)
    {
    }

    Scripting::~Scripting()
    {
    }

    Scripting* Scripting::s_instance = nullptr;

    Scripting& Scripting::get()
    {
        return *s_instance;
    }

    void Scripting::create()
    {
        s_instance = new Scripting();
    }

    void Scripting::destroy()
    {
        delete s_instance;
        s_instance = nullptr;
    }

    void Scripting::setContext(JSContext* context)
    {
        m_context = context;
    }

    jsval Scripting::evaluate(JSObject* object, const std::string& script, const char* filePath, uint32_t line)
    {
        std::vector<uint16_t> u_script = helpers::utf16(script);

        std::string file_name(filePath);
        size_t last_slash = file_name.find_last_of('\\');
        if (last_slash != std::string::npos)
        {
            file_name.erase(0, last_slash + 1);
        }

        std::vector<uint16_t> u_file_name = helpers::utf16(file_name);

        jsval value = 0;

        IRIS_LOG_TRACE("evaluate fileName %s line %d script \"%s\"", file_name.c_str(), line, script.c_str());

        JSBool result = mmEnv.executeScript(
            m_context, object,
            &u_script[0], (uint32_t)u_script.size(),
            &u_file_name[0], line,
            &value);

        IRIS_LOG_TRACE("evaluate result %d value 0x%08x", result, value);

        return value;
    }

};