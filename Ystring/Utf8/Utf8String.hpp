//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "../Encoding.hpp"
#include "../FindFlags.hpp"
#include "../PlatformDetails.hpp"
#include "../SplitFlags.hpp"
#include "../YstringException.hpp"

/** @file
  * @brief The function library for UTF-8 encoded strings.
  */

namespace Ystring { namespace Utf8
{
    /** @brief The result of certain find-functions that accept mutable
      *     strings or their iterators.
      */
    typedef std::pair<std::string::iterator, std::string::iterator>
            StringIteratorPair;

    /** @brief The result of certain find-functions that accept immutable
      *     or their strings.
      */
    typedef std::pair<std::string::const_iterator,
                      std::string::const_iterator>
            StringConstIteratorPair;

    /** @brief Returns true if the upper case versions of @a str and @a cmp
      *     are equal.
      *
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters (the decomposed character is
      *     typically the "lesser" one).
      * @throw YstringException if str contains an invalid UTF-16 code point.
      */
    YSTRING_API bool caseInsensitiveEqual(const std::string& str,
                                          const std::string& cmp);

    /** @brief Returns the number of characters in @a str.
      *
      * @note A composed character can consist of multiple code points.
      * @return the number of characters.
      * @throw YstringException if str contains an invalid UTF-8 code point.
      */
    YSTRING_API size_t countCharacters(const std::string& str);

    /** @brief Returns the number of characters between @a first and @a last.
      *
      * @note A composed character can consist of multiple code points.
      * @return the number of characters.
      * @throw YstringException if str contains an invalid UTF-8 code point.
      */
    YSTRING_API size_t countCharacters(std::string::const_iterator first,
                                       std::string::const_iterator last);

    /** @brief Returns true if @a str ends with @a cmp.
      * @note Composed and decomposed versions of the same characters are
      *     treated as different characters.
      */
    YSTRING_API bool endsWith(const std::string& str,
                              const std::string& cmp,
                              FindFlags_t flags = FindFlags::DEFAULTS);

    /** @brief Return code point at position @a pos in @a str.
      *
      * The first code point has position 0.
      * If @a pos is negative, code points are counted from the end of @a str
      *  where the last character in @a str is at position -1.
      */
    YSTRING_API char32_t getCodePoint(const std::string& str,
                                      ptrdiff_t pos);

    /** @brief Returns the concatenation of the strings in @a strings
      *     delimited by @a delimiter.
      */
    YSTRING_API std::string join(
            const std::vector<std::string>& strings,
            const std::string& delimiter = std::string());

    /** @brief Returns the concatenation of the strings in @a strings
      *     delimited by @a delimiter.
      */
    YSTRING_API std::string join(
            const std::string* strings,
            size_t count,
            const std::string& delimiter = std::string());

    /** @brief Splits @a str where it matches @a sep and returns a list of
      *     the parts.
      * @param maxSplits The maximum number of times @a str will be split.
      *     If the value is 0 @a str wil be split at every newline character.
      *     If the value is negative the splitting will start from the end of
      *     @a str, the result will have parts in reverse order (i.e. the last
      *     part is first, the second to last is second and so on).
      */
    YSTRING_API std::vector<std::string> split(
            const std::string& str,
            const std::string& sep,
            ptrdiff_t maxSplits = 0,
            SplitFlags_t flags = SplitFlags::DEFAULTS);

    /** @brief Splits @a str at characters that satisfy predicate and returns
      *     a list of the parts.
      * @param maxSplits The maximum number of times @a str will be split.
      *     If the value is 0 @a str wil be split at every newline character.
      *     If the value is negative the splitting will start from the end of
      *     @a str, the result will have parts in reverse order (i.e. the last
      *     part is first, the second to last is second and so on).
      */
    YSTRING_API std::vector<std::string> splitIf(
            const std::string& str,
            std::function<bool(char32_t)> predicate,
            ptrdiff_t maxSplits = 0,
            SplitFlags_t flags = SplitFlags::DEFAULTS);

    /** @brief Returns an UTF-8 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::string toUtf8(
            const wchar_t* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-8 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::string toUtf8(
            const char16_t* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-8 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::string toUtf8(
            const char32_t* str, size_t length,
            Encoding_t encoding);

    /** @brief Returns an UTF-8 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::string toUtf8(
            const std::u16string& str,
            Encoding_t encoding = Encoding::UTF_16);

    /** @brief Returns an UTF-8 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::string toUtf8(
            const std::u32string& str,
            Encoding_t encoding = Encoding::UTF_32);

    /** @brief Returns an UTF-8 encoded string equivalent to @a str.
      *
      * @param str The string to convert from.
      * @param encoding The encoding of @a str.
      * @throws YstringException if str contains any characters that aren't
      *     encoded according to @a encoding, or if @a encoding is
      *     unsupported for strings of @a str's type.
      */
    YSTRING_API std::string toUtf8(
            const std::wstring& str,
            Encoding_t encoding);

    /** @brief Returns a copy of @a str where all whitespace characters at the
      *     start and end of the string have been removed.
      */
    YSTRING_API std::string trim(const std::string& str);

}}
