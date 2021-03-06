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

#include "helpers.hpp"

#include "logging/logger.hpp"

namespace iris {
namespace helpers {

    std::string utf8(const std::wstring& text)
    {
        std::string converted;

        int32_t errors;

        size_t size_in_bytes = widetoutf8(text.c_str(), text.size() * UTF8_WCHAR_SIZE, nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return converted;
        }

        converted.resize(size_in_bytes);
        widetoutf8(text.c_str(), text.size() * UTF8_WCHAR_SIZE, &converted[0], size_in_bytes, nullptr);

        return converted;
    }

    std::vector<uint16_t> utf16(const std::string& text)
    {
        std::vector<uint16_t> converted;

        int32_t errors;

        size_t size_in_bytes = utf8toutf16(text.c_str(), text.size(), nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return converted;
        }

        converted.resize(size_in_bytes / sizeof(uint16_t));
        utf8toutf16(text.c_str(), text.size(), &converted[0], size_in_bytes, nullptr);

        return converted;
    }

    std::wstring wide(const std::string& text)
    {
        std::wstring converted;

        int32_t errors;

        size_t size_in_bytes = utf8towide(text.c_str(), text.size(), nullptr, 0, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return converted;
        }

        converted.resize(size_in_bytes / UTF8_WCHAR_SIZE);

        utf8towide(text.c_str(), text.size(), &converted[0], size_in_bytes, nullptr);

        return converted;
    }

    std::string casefold(const std::string& text)
    {
        std::string converted;

        int32_t errors;

        size_t size_in_bytes = utf8casefold(text.c_str(), text.size(), nullptr, 0, UTF8_LOCALE_DEFAULT, &errors);
        if (size_in_bytes == 0 ||
            errors != UTF8_ERR_NONE)
        {
            return converted;
        }

        converted.resize(size_in_bytes);
        utf8casefold(text.c_str(), text.size(), &converted[0], size_in_bytes, UTF8_LOCALE_DEFAULT, nullptr);

        return converted;
    }

    bool createDirectory(const std::string& path)
    {
        std::wstring wide_path = wide(path);

        return ::SHCreateDirectoryExW(nullptr, wide_path.c_str(), nullptr) == TRUE;
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

    std::string fileLastModifiedTime(const std::string& path)
    {
        std::wstring wide_path = wide(path);

        HANDLE file;
        FILETIME write_file_time;
        SYSTEMTIME write_system_time;

         if ((file = ::CreateFileW(wide_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr)) == INVALID_HANDLE_VALUE ||
            ::GetFileTime(file, nullptr, nullptr, &write_file_time) == FALSE ||
            ::FileTimeToSystemTime(&write_file_time, &write_system_time) == FALSE)
        {
            return std::string("");
        }

        ::CloseHandle(file);

        char buffer[256] = { 0 };
        sprintf_s(buffer, "%04d-%02d-%02dT%02d:%02d:%02d.%04dZ",
            write_system_time.wYear, write_system_time.wMonth, write_system_time.wDay,
            write_system_time.wHour, write_system_time.wMinute, write_system_time.wSecond, write_system_time.wMilliseconds);

        return std::string(buffer);
    }

    std::string absolutePath(const std::string& path)
    {
        std::wstring wide_path = wide(path);

        wchar_t buffer[_MAX_PATH + 1] = { 0 };
        ::GetFullPathNameW(wide_path.c_str(), _MAX_PATH, buffer, nullptr);

        return utf8(buffer);
    }

    std::string relativePath(const std::string& pathFrom, const std::string& pathTo)
    {
        std::wstring wide_from = wide(pathFrom);
        std::wstring wide_to = wide(pathTo);

        wchar_t buffer[_MAX_PATH] = { 0 };

        ::PathRelativePathToW(
            buffer,
            wide_from.c_str(), FILE_ATTRIBUTE_DIRECTORY,
            wide_to.c_str(), FILE_ATTRIBUTE_NORMAL);

        return utf8(buffer);
    }

    std::string uriToAbsolute(const std::string& uri)
    {
        static const char* Identifier = "file:///";
        static const size_t IdentifierLength = strlen(Identifier);

        if (uri.length() < IdentifierLength ||
            uri.compare(0, IdentifierLength, Identifier) != 0)
        {
            return uri;
        }

        std::string path = uri.substr(IdentifierLength, uri.length() - IdentifierLength);

        size_t drive_separator = path.find('|');
        if (drive_separator != std::string::npos)
        {
            path.replace(drive_separator, drive_separator + 1, 1, ':');
        }

        return absolutePath(path);
    }

    std::string absolutePathToUri(const std::string& path)
    {
        std::string uri = std::string("file:///") + path;

        std::replace(uri.begin() + 6, uri.end(), ':', '|');
        std::replace(uri.begin(), uri.end(), '\\', '/');

        return uri;
    }

    std::string readElementText(TiXmlElement* parent, const char* name)
    {
        TiXmlElement* element = parent->FirstChildElement(name);
        if (element == nullptr)
        {
            IRIS_LOG_ERROR("Missing \"%s\" element under \"%s\".", name, parent->Value());

            return std::string("");
        }

        const char* text = element->GetText();

        return (text != nullptr) ? std::string(text) : "";
    }

    std::string readAttributeText(TiXmlElement* owner, const char* name)
    {
        const char* value = owner->Attribute(name);
        return std::string((value != nullptr) ? value : "");
    }

};
};