//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Formatters.hpp"
#include "../Ystring/Utf8.hpp"

namespace Ytest {

using namespace Ytest_Ystring;

std::ostream& operator<<(std::ostream& os, const std::wstring& s)
{
    return os << Utf8::toUtf8(s, Encoding::UTF_16);
}

std::ostream& operator<<(std::ostream& os, const wchar_t* s)
{
    return os << Utf8::toUtf8(s, Encoding::UTF_16);
}

}
