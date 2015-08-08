//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

static_assert(sizeof(wchar_t) == 2,
              "wchar_t isn't 16-bit and isn't suited for UTF-16.");

#include "Utf16/Utf16WString.hpp"
