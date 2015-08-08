//****************************************************************************
// Copyright © 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <iterator>
#include <limits>
#include "../DecoderResult.hpp"

/** @file
  * @brief Defines functions for working with UTF-8 encoded strings.
  */

namespace Ystring { namespace Utf8 {

template <typename FwdIt>
bool isValidUtf8(FwdIt begin, FwdIt end, bool acceptIncompleteAtEnd = false);

/** @brief Assigns to @a codePoint the code point starting at @a it.
  *
  * @note The function returns false both when it has reached the end of the
  *     string and when it has encountered an invalid byte. The caller must
  *     compare @a it with @a end to determine why the result is false.
  *
  * @param codePoint is assigned the code point starting at @a it.
  * @param it        start of the code point. Has been advanced to the start
  *     of the next code point upon return, or one byte past the first
  *     invalid byte in the current code point.
  * @param end       the end of the string.
  */
template <typename FwdIt>
DecoderResult_t nextUtf8CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

/** @brief Assigns the code point ending at @a it to @a codePoint.
  */
template <typename BiIt>
DecoderResult_t prevUtf8CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename FwdIt>
bool skipNextUtf8CodePoint(FwdIt& it, FwdIt end);

template <typename BiIt>
bool skipPrevUtf8CodePoint(BiIt begin, BiIt& it);

}}

#include "DecodeUtf8-impl.hpp"
