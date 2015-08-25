//****************************************************************************
// Copyright � 2015, Jan Erik Breimo.
// Created 2015-07-10 by Jan Erik Breimo
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstdint>

/** @file
  * @brief Defines constants and macros shared by all the other files
  *     in @a JEBString.
  */

/// @cond
#define YSTRING_API

/// @endcond

/** @brief The top-level namespace for all functions and classes
  *     in @a Ystring.
  */
namespace Ystring
{
    /** @brief The maxmum value for unicode code points.
      */
    static const uint32_t UNICODE_MAX = (1 << 20) - 1;

    /** @brief A value representing invalid code points.
      */
    static const uint32_t INVALID_CHAR = 0xFFFFFFFFul;
}
