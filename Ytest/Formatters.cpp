//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-28.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Formatters.hpp"
#include "../Ystring/Streaming/StreamOperators.hpp"

namespace Ytest
{
    std::ostream& operator<<(std::ostream& os, const std::wstring& s)
    {
        return Ystring::operator<<(os, s);
    }

    std::ostream& operator<<(std::ostream& os, const wchar_t* s)
    {
        return Ystring::operator<<(os, s);
    }

    std::ostream& operator<<(std::ostream& os, const std::u16string& s)
    {
        return Ystring::operator<<(os, s);
    }

    std::ostream& operator<<(std::ostream& os, const char16_t* s)
    {
        return Ystring::operator<<(os, s);
    }

    std::ostream& operator<<(std::ostream& os, const std::u32string& s)
    {
        return Ystring::operator<<(os, s);
    }

    std::ostream& operator<<(std::ostream& os, const char32_t* s)
    {
        return Ystring::operator<<(os, s);
    }
}