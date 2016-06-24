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