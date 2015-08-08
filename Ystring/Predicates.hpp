//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Unicode/UnicodePredicates.hpp"

namespace Ystring {

bool isPathSeparator(uint32_t chr);

bool isWindowsPathSeparator(uint32_t chr);

bool isPosixPathSeparator(uint32_t chr);

}
