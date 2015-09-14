//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 13.09.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "StreamOperators.hpp"
#include "../Utf8.hpp"

namespace Ystring
{
    #ifdef YSTRING_WCHAR_IS_2_BYTES

    std::ostream& operator<<(std::ostream& os, const std::wstring& s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_16);
    }

    std::ostream& operator<<(std::ostream& os, const wchar_t* s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_16);
    }

    #else

    std::ostream& operator<<(std::ostream& os, const std::wstring& s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_32);
    }

    std::ostream& operator<<(std::ostream& os, const wchar_t* s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_32);
    }

    #endif

    std::ostream& operator<<(std::ostream& os, const std::u16string& s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_16);
    }

    std::ostream& operator<<(std::ostream& os, const char16_t* s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_16);
    }

    std::ostream& operator<<(std::ostream& os, const std::u32string& s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_32);
    }

    std::ostream& operator<<(std::ostream& os, const char32_t* s)
    {
        return os << Utf8::toUtf8(s, Encoding::UTF_32);
    }
}
