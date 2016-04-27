//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "YstringDefinitions.hpp"
#include "Unicode/UnicodePredicates.hpp"

/** @file
  * @brief Defines character predicates.
  */

namespace Ystring
{
    YSTRING_API bool isPathSeparator(char32_t chr);
    YSTRING_API bool isWindowsPathSeparator(char32_t chr);
    YSTRING_API bool isPosixPathSeparator(char32_t chr);
}
