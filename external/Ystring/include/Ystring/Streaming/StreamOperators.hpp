//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 13.09.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ostream>
#include "Ystring/PlatformDetails.hpp"

namespace Ystring
{
    std::ostream& operator<<(std::ostream& os, const std::wstring& s);

    std::ostream& operator<<(std::ostream& os, const wchar_t* s);

    std::ostream& operator<<(std::ostream& os, const std::u16string& s);

    std::ostream& operator<<(std::ostream& os, const char16_t* s);

    std::ostream& operator<<(std::ostream& os, const std::u32string& s);

    std::ostream& operator<<(std::ostream& os, const char32_t* s);
}
