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

#ifdef _WIN32
    #ifdef YSTRING_EXPORTS
        #define YSTRING_API __declspec(dllexport)
    #else
        #define YSTRING_API
        #ifdef _DEBUG
            #pragma comment (lib, "Ystring.lib")
        #else
            #pragma comment (lib, "Ystring.lib")
        #endif
    #endif
#else
    #define YSTRING_API
#endif

/// @endcond

/** @brief The top-level namespace for all functions and classes
  *     in @a Ystring.
  */
namespace Ystring
{
    static const uint32_t UNICODE_MAX = (1 << 20) - 1;
    static const uint32_t INVALID_CHAR = 0xFFFFFFFFul;
}
