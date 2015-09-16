//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include "CharClass.hpp"
#include "UnicodeChars.hpp"

/** @file
  * @brief Defines predicates for testing properties of unicode code-points.
  */

namespace Ystring { namespace Unicode
{
    /** @brief Returns true if @a c is a letter or a number.
      */
    inline bool isAlphaNumeric(uint32_t c)
    {
        return (getCharClass(c) & (CharClass::LETTER | CharClass::NUMBER)) != 0;
    }

    /** @brief Returns true if @a c is a letter that is lowercased, uppercased
      *     titlecased.
      */
    inline bool isCasedLetter(uint32_t c)
    {
        return (getCharClass(c) & CharClass::CASED_LETTER) != 0;
    }

    /** @brief Returns true if @a c is one of the control characters.
      */
    inline bool isControl(uint32_t c)
    {
        return (getCharClass(c) & CharClass::CONTROL) != 0;
    }

    /** @brief Returns true if @a c is one of the formatting characters.
      */
    inline bool isFormat(uint32_t c)
    {
        return (getCharClass(c) & CharClass::FORMAT) != 0;
    }

    /** @brief Returns true if @a c is a character that can be drawn
      *     in any way.
      */
    inline bool isGraphical(uint32_t c)
    {
        return (getCharClass(c) & (CharClass::LETTER |
                                   CharClass::MARK |
                                   CharClass::NUMBER |
                                   CharClass::PUNCTUATION |
                                   CharClass::SYMBOL)) != 0;
    }

    /** @brief Returns true if @a c is among the hexadecimal
      *     digits (0-9 and A-F).
      */
    inline bool isHexDigit(uint32_t c)
    {
        return ('0' <= c && c <= '9') ||
               ('A' <= c && c <= 'F') ||
               ('a' <= c && c <= 'f');
    }

    /** @brief Returns true if @a c is a letter.
      */
    inline bool isLetter(uint32_t c)
    {
        return (getCharClass(c) & CharClass::LETTER) != 0;
    }

    /** @brief Returns true if @a c is a combining mark.
      */
    inline bool isMark(uint32_t c)
    {
        return (getCharClass(c) & CharClass::MARK) != 0;
    }

    /** @brief Returns true if @a c is among the characters used to represent
      * newlines.
      *
      * @note Windows (and MSDOS) uses the sequence of "\\r\\n" to represent
      *     newlines and isNewLine will return true for both of these.
      */
    inline bool isNewline(uint32_t c)
    {
        return c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
               c == Unicode::NEXT_LINE || c == Unicode::LINE_SEPARATOR ||
               c == Unicode::PARAGRAPH_SEPARATOR;
    }

    /** @brief Returns true if @a c is a number.
      *
      * @note Unicode supports numbers from all written languages, not
      *     just the western numbers 0-9.
      */
    inline bool isNumber(uint32_t c)
    {
        return (getCharClass(c) & CharClass::NUMBER) != 0;
    }

    /** @brief Returns true if @a c is a punctuation symbol.
      */
    inline bool isPunctuation(uint32_t c)
    {
        return (getCharClass(c) & CharClass::PUNCTUATION) != 0;
    }

    /** @brief Returns true if @a c is a separator of one kind or another.
      */
    inline bool isSeparator(uint32_t c)
    {
        return (getCharClass(c) & CharClass::SEPARATOR) != 0;
    }

    /** @brief Returns true if @a c is one of the values used to compose
      *     surrogate pairs.
      */
    inline bool isSurrogate(uint32_t c)
    {
        return (getCharClass(c) & CharClass::SURROGATE) != 0;
    }

    /** @brief Returns true if @a c is one of the unicode symbols.
      */
    inline bool isSymbol(uint32_t c)
    {
        return (getCharClass(c) & CharClass::SYMBOL) != 0;
    }

    /** @brief Returns true if @a c is a visible character.
      *
      * Visible characters are the sum of graphical characters and separators.
      */
    inline bool isVisible(uint32_t c)
    {
        return (getCharClass(c) & (CharClass::LETTER |
                                   CharClass::MARK |
                                   CharClass::NUMBER |
                                   CharClass::PUNCTUATION |
                                   CharClass::SYMBOL |
                                   CharClass::SEPARATOR)) != 0;
    }

    /** @brief Returns true if @a c is a whitespace character.
      *
      * The whitespace character class include tab, newlines, space and all
      * separator characters.
      */
    inline bool isWhitespace(uint32_t c)
    {
        return c == '\t' || c == ' ' || isNewline(c) ||
               (c > 128 && (getCharClass(c) & CharClass::SEPARATOR) != 0);
    }
}}
