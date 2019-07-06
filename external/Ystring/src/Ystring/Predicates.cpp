//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Predicates.hpp"

namespace Ystring
{
    #ifdef _WIN32

    bool isPathSeparator(char32_t chr)
    {
        return isWindowsPathSeparator(chr);
    }

    #else

    bool isPathSeparator(char32_t chr)
    {
        return isWindowsPathSeparator(chr);
    }

    #endif

    bool isWindowsPathSeparator(char32_t chr)
    {
        return chr == '/' || chr == '\\';
    }

    bool isPosixPathSeparator(char32_t chr)
    {
        return chr == '/';
    }
}
