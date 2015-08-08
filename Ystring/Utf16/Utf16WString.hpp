//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "../Encoding.hpp"
#include "../EscapeType.hpp"
#include "../FindFlags.hpp"
#include "../SplitFlags.hpp"
#include "../YstringException.hpp"

/** @file
  * @brief The function library for UTF-16 encoded wstrings.
  */

namespace Ystring { namespace Utf16W {

/** @brief The result of certain find-functions that accept mutable
  *     strings or their iterators.
  */
typedef std::pair<std::wstring::iterator, std::wstring::iterator>
        StringIteratorPair;

/** @brief The result of certain find-functions that accept immutable
  *     or their strings.
  */
typedef std::pair<std::wstring::const_iterator, std::wstring::const_iterator>
        StringConstIteratorPair;

/** @brief Adds @a codePoint encoded as UTF-16 to the end of @a str.
  */
YSTRING_API std::wstring& append(std::wstring& str, uint32_t chr);

/** @brief Compares @a str and @a cmp, ignoring any differences in
  *     letter casing.
  *
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  * @returns @arg < 0 if @a str is less than @a cmp
  *          @arg 0 if @a str is equal to @a cmp
  *          @arg > 0 if @a str is greater than @a cmp
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API int32_t caseInsensitiveCompare(const std::wstring& str,
                                           const std::wstring& cmp);

/** @brief Returns true if the upper case versions of @a str and @a cmp
  *     are equal.
  *
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API bool caseInsensitiveEqual(const std::wstring& str,
                                      const std::wstring& cmp);

/** @brief Returns true if the upper case version of @a str is less
  *     than @a cmp.
  *
  * Only a quick comparison of code point values are performed. This
  * function should not be used to sort strings in alphabetical order as
  * what is alphabetical order varies between languages and cultures.
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API bool caseInsensitiveLess(const std::wstring& str,
                                     const std::wstring& cmp);

/** @brief Returns true if @a str contains code point @a chr.
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API bool contains(const std::wstring& str, uint32_t chr);

/** @brief Returns the number of characters in @a str.
  *
  * @note A composed character can consist of multiple code points.
  * @return the number of characters.
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API size_t countCharacters(const std::wstring& str);

/** @brief Returns the number of code points in @a str.
  *
  * @note A composed character can consist of multiple code points.
  * @return the number of code points.
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API size_t countCodePoints(const std::wstring& str);

/** @brief Returns true if @a str ends with @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API bool endsWith(const std::wstring& str,
                          const std::wstring& cmp,
                          FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns a copy of @a str where control character etc. have been
  *     escaped.
  *
  * When escaping with backslashes the function does not use octal codes,
  * not even \\0 for value 0 as these are too easy to mis-interprete.
  */
YSTRING_API std::wstring escape(const std::wstring& str,
                                EscapeType_t type = EscapeType::BACKSLASH);

/** @brief Returns the first substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringIteratorPair findFirst(
        std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringConstIteratorPair findFirst(
        const std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringIteratorPair findFirst(
        std::wstring::iterator first,
        std::wstring::iterator last,
        const std::wstring& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringConstIteratorPair findFirst(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last,
        const std::wstring& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringIteratorPair findFirstNewline(std::wstring& str);

/** @brief Returns the first substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringConstIteratorPair findFirstNewline(const std::wstring& str);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringIteratorPair findFirstNewline(std::wstring::iterator first,
                                                std::wstring::iterator last);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringConstIteratorPair findFirstNewline(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last);

/** @brief Returns the last substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringIteratorPair findLast(
        std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringConstIteratorPair findLast(
        const std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringIteratorPair findLast(
      std::wstring::iterator first,
      std::wstring::iterator last,
      const std::wstring& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
YSTRING_API StringConstIteratorPair findLast(
      std::wstring::const_iterator first,
      std::wstring::const_iterator last,
      const std::wstring& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringIteratorPair findLastNewline(std::wstring& str);

/** @brief Returns the last substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringConstIteratorPair findLastNewline(const std::wstring& str);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringIteratorPair findLastNewline(std::wstring::iterator first,
                                               std::wstring::iterator last);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
YSTRING_API StringConstIteratorPair findLastNewline(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last);

/** @brief Inserts string @a sub into @a str at position @a pos.
  *
  * @param pos The insert position in complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  * @YSTRING_THROW if @a str isn't a valid UTF-16 string.
  */
YSTRING_API std::wstring insert(const std::wstring& str,
                                ptrdiff_t pos,
                                const std::wstring& sub);

/** @brief Inserts character @a chr into @a str at position @a pos.
  *
  * @param pos The insert position in complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  * @YSTRING_THROW if @a str isn't a valid UTF-16 string.
  */
YSTRING_API std::wstring insert(const std::wstring& str,
                                ptrdiff_t pos,
                                uint32_t chr);

/** @brief Returns true if all characters in @a str are either
  *     letters or numbers.
  * @YSTRING_THROW if str contains an invalid UTF-16 code point.
  */
YSTRING_API bool isAlphaNumeric(const std::wstring& str);

/** @brief Returns true if all characters in the range from @a first
  *     to @a last are either letters or numbers.
  * @YSTRING_THROW if str contains an invalid UTF-16 code point.
  */
YSTRING_API bool isAlphaNumeric(std::wstring::iterator first,
                                std::wstring::iterator last);

/** @brief Returns true if all characters in the range from @a first
  *     to @a last are either letters or numbers.
  * @YSTRING_THROW if str contains an invalid UTF-16 code point.
  */
YSTRING_API bool isAlphaNumeric(std::wstring::const_iterator first,
                                std::wstring::const_iterator last);

///** @brief Returns true if all characters in @a str are valid UTF-16.
//  */
//YSTRING_API bool isValidUtf16(const std::wstring& str);

/** @brief Returns the concatenation of the strings in @a strings delimited
  * by @a delimiter.
  */
YSTRING_API std::wstring join(
        const std::vector<std::wstring>& strings,
        const std::wstring& delimiter = std::wstring());

/** @brief Returns the concatenation of the strings in @a strings delimited
  * by @a delimiter.
  */
YSTRING_API std::wstring join(
        const std::wstring* strings,
        size_t count,
        const std::wstring& delimiter = std::wstring());

/** @brief Returns a lower case copy of @a str.
  */
YSTRING_API std::wstring lower(const std::wstring& str);

/** @brief Returns an iterator to the start of character number @a n
  *     starting at @a first.
  */
YSTRING_API std::wstring::iterator nextCharacter(
        std::wstring::iterator& first,
        std::wstring::iterator& last,
        size_t n = 1);

/** @brief Returns an iterator to the start of character number @a n
  *     starting at @a first.
  */
YSTRING_API std::wstring::const_iterator nextCharacter(
        std::wstring::const_iterator& first,
        std::wstring::const_iterator& last,
        size_t n = 1);

/** @brief Returns an iterator to the start of character number @a n
  *     from the start of string @a str.
  * @param n The number of complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  */
YSTRING_API std::wstring::iterator nthCharacter(
        std::wstring& str,
        ptrdiff_t n);

/** @brief Returns an iterator to the start of character number @a n
  *     from the start of string @a str.
  * @param n The number of complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  */
YSTRING_API std::wstring::const_iterator nthCharacter(
        const std::wstring& str,
        ptrdiff_t n);

/** @brief Returns an iterator to the start of character number @a n
  *     counting backwards from @a last.
  */
YSTRING_API std::wstring::iterator prevCharacter(
        std::wstring::iterator& first,
        std::wstring::iterator& last,
        size_t n = 1);

/** @brief Returns an iterator to the start of character number @a n
  *     counting backwards from @a last.
  */
YSTRING_API std::wstring::const_iterator prevCharacter(
        std::wstring::const_iterator& first,
        std::wstring::const_iterator& last,
        size_t n = 1);

/** @brief Returns a copy of @a str where instances of @a from are replaced
  *     with @a to.
  *
  * @param maxReplacements The maximum number of replacements that will be
  *     performed. All  instances of @a from are replaced if the value is 0.
  *     If it is negative at most abs(maxReplacements) will be made, starting
  *     at the end of the string.
  */
YSTRING_API std::wstring replace(
        const std::wstring& str,
        const std::wstring& from,
        const std::wstring& to,
        ptrdiff_t maxReplacements = 0,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns a copy of @a str where the substring between @a start and
  *     @a end has been replaced with @a repl.
  *
  * @param maxReplacements The maximum number of replacements that will be
  *     performed. All  instances of @a from are replaced if the value is 0.
  *     If it is negative at most abs(maxReplacements) will be made, starting
  *     at the end of the string.
  */
YSTRING_API std::wstring replace(
        const std::wstring& str,
        ptrdiff_t start,
        ptrdiff_t end,
        const std::wstring& repl);

/** @brief Returns a copy of @a str with instances of @a from replaced
  *     with @a to.
  *
  * @param fromChar The character to replace
  * @param toChar The replacement
  * @param maxReplacements The maximum number of replacements that will be
  *     performed. All  instances of @a from are replaced if the value is 0.
  *     If it is negative at most abs(maxReplacements) will be made, starting
  *     at the end of the string.
  */
YSTRING_API std::wstring replaceCodePoint(
        const std::wstring& s,
        uint32_t from,
        uint32_t to,
        ptrdiff_t maxReplacements = 0);

/** @brief Returns a copy of @a str where all invalid code points have been
 *     replaced with @a chr.
 */
YSTRING_API std::wstring replaceInvalidUtf16(const std::wstring& str,
                                             uint32_t chr = '?');

/** @brief Replaces all invalid code points in @a str with @a chr.
 */
YSTRING_API std::wstring& replaceInvalidUtf16InPlace(std::wstring& str,
                                                     char chr = '?');

/** @brief Returns a reversed copy of @a str.
  *
  * Characters with combining marks are left intact.
  */
YSTRING_API std::wstring reverse(const std::wstring& str);

/** @brief Splits @a str where it contains whitespace characters and returns
  *     a list of the parts.
  * @param maxSplits The maximum number of times @a str will be split. If the
  *     value is 0 @a str wil be split at every newline character. If the
  *     value is negative the splitting will start from the end of @a str,
  *     the result will have parts in reverse order (i.e. the last part is
  *     first, the second to last is second and so on).
  */
YSTRING_API std::vector<std::wstring> split(
        const std::wstring& str,
        ptrdiff_t maxSplits = 0,
        SplitFlags_t flags = SplitFlags::IGNORE_EMPTY);

/** @brief Splits @a str where it matches @a sep and returns a list of
  *     the parts.
  * @param maxSplits The maximum number of times @a str will be split. If the
  *     value is 0 @a str wil be split at every newline character. If the
  *     value is negative the splitting will start from the end of @a str,
  *     the result will have parts in reverse order (i.e. the last part is
  *     first, the second to last is second and so on).
  */
YSTRING_API std::vector<std::wstring> split(
        const std::wstring& str,
        const std::wstring& sep,
        ptrdiff_t maxSplits = 0,
        SplitFlags_t flags = SplitFlags::DEFAULTS);

/** @brief Splits @a str at characters that satisfy predicate and returns a
  *     list of the parts.
  * @param maxSplits The maximum number of times @a str will be split. If the
  *     value is 0 @a str wil be split at every newline character. If the
  *     value is negative the splitting will start from the end of @a str,
  *     the result will have parts in reverse order (i.e. the last part is
  *     first, the second to last is second and so on).
  */
YSTRING_API std::vector<std::wstring> splitIf(
        const std::wstring& str,
        std::function<bool(uint32_t)> predicate,
        ptrdiff_t maxSplits = 0,
        SplitFlags_t flags = SplitFlags::DEFAULTS);

/** @brief Splits @a str at newline characters and returns a list
  *     of the parts.
  * @param maxSplits The maximum number of times @a str will be split. If the
  *     value is 0 @a str wil be split at every newline character. If the
  *     value is negative the splitting will start from the end of @a str,
  *     the result will have parts in reverse order (i.e. the last part is
  *     first, the second to last is second and so on).
  */
YSTRING_API std::vector<std::wstring> splitLines(
        const std::wstring& str,
        ptrdiff_t maxSplits = 0,
        SplitFlags_t flags = SplitFlags::DEFAULTS);

/** @brief Returns true if @a str starts with substring @a cmp.
  * @throw logic_error if @a str or @a cmp contain any invalid UTF-16
  *     code points.
  */
YSTRING_API bool startsWith(const std::wstring& str,
                            const std::wstring& cmp,
                            FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the substring of of @a str that starts at character number
  *     @a startIndex and ends at character number @a endIndex.
  * @param startIndex The start position in complete characters (i.e. not
  *     bytes, not even code points if the string has decomposed characters)
  *     from the start of the string. If @a startIndex is negative it's from
  *     the end of the string instead.
  * @param endIndex The end position in complete characters (i.e. not
  *     bytes, not even code points if the string has decomposed characters)
  *     from the start of the string. If @a startIndex is negative it's from
  *     the end of the string instead.
  * @throw logic_error if str contains an invalid UTF-16 code point.
  */
YSTRING_API std::wstring substring(const std::wstring& str,
                                  ptrdiff_t startIndex,
                                  ptrdiff_t endIndex = PTRDIFF_MAX);

/** @brief Returns a titlecased copy of @a str.
  */
YSTRING_API std::wstring title(const std::wstring& str);

/** @brief Returns a UTF-16 encoded string representing @a chr
  */
YSTRING_API std::wstring toUtf16(uint32_t chr);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const std::string& str, Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const char* str, size_t length,
                                 Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const wchar_t* str, size_t length,
                                 Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const uint16_t* str, size_t length,
                                 Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const uint32_t* str, size_t length,
                                 Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const std::u16string& str,
                                 Encoding_t encoding = Encoding::UTF_16);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const std::u32string& str,
                                 Encoding_t encoding = Encoding::UTF_32);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const char16_t* str, size_t length,
                                 Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(const char32_t* str, size_t length,
                                 Encoding_t encoding);

/** @brief Returns an UTF-16 encoded string equivalent to @a str.
  *
  * @param str The string to convert from.
  * @param encoding The encoding of @a str.
  * @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
YSTRING_API std::wstring toUtf16(
        const std::wstring& str,
        Encoding_t encoding);

/** @brief Returns a copy of @a str where all whitespace characters at the
  *     start and end of the string have been removed.
  */
YSTRING_API std::wstring trim(const std::wstring& str);

/** @brief Returns a copy of @a str where all characters staisfying
 *      @a predicate at the start and end of the string have been removed.
  */
YSTRING_API std::wstring trim(
        const std::wstring& str,
        std::function<bool(uint32_t)> predicate);

/** @brief Returns a copy of @a str where all whitespace characters at the
  *     end of the string have been removed.
  */
YSTRING_API std::wstring trimEnd(const std::wstring& str);

/** @brief Returns a copy of @a str where all characters staisfying
 *      @a predicate at the end of the string have been removed.
  */
YSTRING_API std::wstring trimEnd(
        const std::wstring& str,
        std::function<bool(uint32_t)> predicate);

/** @brief Returns a copy of @a str where all whitespace characters at the
  *     start of the string have been removed.
  */
YSTRING_API std::wstring trimStart(const std::wstring& str);

/** @brief Returns a copy of @a str where all characters that satisfy
 *      @a predicate at the start of the string have been removed.
  */
YSTRING_API std::wstring trimStart(
        const std::wstring& str,
        std::function<bool(uint32_t)> predicate);

/** @brief Returns a copy of @a str where all escape sequences have been
  *     translated to the characters they represent.
  * @throws logic_error if @a str contains an invalid escape sequence.
  */
YSTRING_API std::wstring unescape(
        const std::wstring& str,
        EscapeType_t type = EscapeType::BACKSLASH);

/** @brief Returns a upper case copy of @a str.
  */
YSTRING_API std::wstring upper(const std::wstring& str);

}}
