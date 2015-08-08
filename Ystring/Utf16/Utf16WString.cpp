//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf16WString.hpp"

#include "../PlatformDetails.hpp"
#include "../Generic/GenericString.hpp"
#include "../CodePage/CodePageEncoding.hpp"
#include "../Utf8/Utf8Encoding.hpp"
#include "../Utf32/Utf32Encoding.hpp"
#include "Utf16Encoding.hpp"

namespace Ystring { namespace Utf16W {

using Generic::makeStringReference;
using Generic::makeRange;
using Generic::fromRange;
using Utf16::Utf16Encoding;
using Utf16::encodeUtf16;
using Utf16::nextUtf16CodePoint;

std::wstring& append(std::wstring& str, uint32_t chr)
{
    append(makeStringReference(str), chr, Utf16Encoding());
    return str;
}

int32_t caseInsensitiveCompare(const std::wstring& str, const std::wstring& cmp)
{
    return Generic::caseInsensitiveCompare(makeRange(str),
                                           makeRange(cmp),
                                           Utf16Encoding());
}

bool caseInsensitiveEqual(const std::wstring& str, const std::wstring& cmp)
{
    return Generic::caseInsensitiveEqual(makeRange(str),
                                         makeRange(cmp),
                                         Utf16Encoding());
}

bool caseInsensitiveLess(const std::wstring& str, const std::wstring& cmp)
{
    return Generic::caseInsensitiveLess(makeRange(str),
                                        makeRange(cmp),
                                        Utf16Encoding());
}

bool contains(const std::wstring& str, uint32_t chr)
{
    return Generic::contains(makeRange(str), chr, Utf16Encoding());
}

size_t countCharacters(const std::wstring& str)
{
    return Generic::countCharacters(makeRange(str), Utf16Encoding());
}

size_t countCodePoints(const std::wstring& str)
{
    return Generic::countCodePoints(makeRange(str), Utf16Encoding());
}

bool endsWith(const std::wstring& str,
              const std::wstring& cmp,
              FindFlags_t flags)
{
    return Generic::endsWith(
            makeRange(str),
            makeRange(cmp),
            Utf16Encoding(),
            flags);
}

std::wstring escape(const std::wstring& str, EscapeType_t mode)
{
    return Generic::escape<std::wstring>(makeRange(str), mode, Utf16Encoding());
}

StringIteratorPair findFirst(
        std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(str), makeRange(cmp), Utf16Encoding(),
                              flags);
}

StringConstIteratorPair findFirst(
        const std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(str), makeRange(cmp), Utf16Encoding(),
                              flags);
}

StringIteratorPair findFirst(
        std::wstring::iterator first,
        std::wstring::iterator last,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                              Utf16Encoding(), flags);
}

StringConstIteratorPair findFirst(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                              Utf16Encoding(), flags);
}

StringIteratorPair findFirstNewline(std::wstring& str)
{
    return Generic::findFirstNewline(makeRange(str), Utf16Encoding());
}

StringConstIteratorPair findFirstNewline(const std::wstring& str)
{
    return Generic::findFirstNewline(makeRange(str), Utf16Encoding());
}

StringIteratorPair findFirstNewline(
        std::wstring::iterator first,
        std::wstring::iterator last)
{
    return Generic::findFirstNewline(makeRange(first, last), Utf16Encoding());
}

StringConstIteratorPair findFirstNewline(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last)
{
    return Generic::findFirstNewline(makeRange(first, last), Utf16Encoding());
}

StringIteratorPair findLast(
        std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(str), makeRange(cmp), Utf16Encoding(),
                             flags);
}

StringConstIteratorPair findLast(
        const std::wstring& str,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(str), makeRange(cmp), Utf16Encoding(),
                             flags);
}

StringIteratorPair findLast(
        std::wstring::iterator first,
        std::wstring::iterator last,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(first, last), makeRange(cmp), Utf16Encoding(),
                            flags);
}

StringConstIteratorPair findLast(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last,
        const std::wstring& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(first, last), makeRange(cmp),
                             Utf16Encoding(), flags);
}

StringIteratorPair findLastNewline(std::wstring& str)
{
    return Generic::findLastNewline(makeRange(str), Utf16Encoding());
}

StringConstIteratorPair findLastNewline(const std::wstring& str)
{
    return Generic::findLastNewline(makeRange(str), Utf16Encoding());
}

StringIteratorPair findLastNewline(
        std::wstring::iterator first,
        std::wstring::iterator last)
{
    return Generic::findLastNewline(makeRange(first, last), Utf16Encoding());
}

StringConstIteratorPair findLastNewline(
        std::wstring::const_iterator first,
        std::wstring::const_iterator last)
{
    return Generic::findLastNewline(makeRange(first, last), Utf16Encoding());
}

std::wstring insert(const std::wstring& str, ptrdiff_t pos,
                   const std::wstring& sub)
{
    return Generic::insert<std::wstring>(makeRange(str), pos, makeRange(sub),
                                        Utf16Encoding());
}

std::wstring insert(const std::wstring& str, ptrdiff_t pos, uint32_t chr)
{
    return Generic::insert<std::wstring>(makeRange(str), pos, chr,
                                        Utf16Encoding());
}

bool isAlphaNumeric(const std::wstring& str)
{
    return isAlphaNumeric(makeRange(str), Utf16Encoding());
}

bool isAlphaNumeric(std::wstring::iterator first,
                    std::wstring::iterator last)
{
    return isAlphaNumeric(makeRange(first, last), Utf16Encoding());
}

bool isAlphaNumeric(std::wstring::const_iterator first,
                    std::wstring::const_iterator last)
{
    return isAlphaNumeric(makeRange(first, last), Utf16Encoding());
}

//bool isValidUtf16(const std::wstring& str)
//{
//    return isValidUtf16(begin(str), end(str));
//}

std::wstring join(const std::vector<std::wstring>& strings,
                 const std::wstring& delimiter)
{
    return join(strings.data(), strings.size(), delimiter);
}

std::wstring join(const std::wstring* strings,
                 size_t count,
                 const std::wstring& delimiter)
{
    return delimiter.empty() ?
           Generic::join<std::wstring>(strings, strings + count) :
           Generic::join<std::wstring>(strings, strings + count,
                                      makeRange(delimiter));
}

std::wstring lower(const std::wstring& str)
{
    return Generic::lower<std::wstring>(makeRange(str), Utf16Encoding());
}

std::wstring::iterator nextCharacter(std::wstring::iterator& first,
                                    std::wstring::iterator& last,
                                    size_t n)
{
    return Generic::nextCharacter(makeRange(first, last), n ,
                                  Utf16Encoding());
}

std::wstring::const_iterator nextCharacter(std::wstring::const_iterator& first,
                                          std::wstring::const_iterator& last,
                                          size_t n)
{
    return Generic::nextCharacter(makeRange(first, last), n,
                                  Utf16Encoding());
}

std::wstring::iterator nthCharacter(std::wstring& str, ptrdiff_t n)
{
    return Generic::nthCharacter(makeRange(str), n, Utf16Encoding());
}

std::wstring::const_iterator nthCharacter(const std::wstring& str,
                                         ptrdiff_t n)
{
    return Generic::nthCharacter(makeRange(str), n, Utf16Encoding());
}

std::wstring::iterator prevCharacter(std::wstring::iterator& first,
                                    std::wstring::iterator& last,
                                    size_t n)
{
    return Generic::prevCharacter(makeRange(first, last), n ,
                                  Utf16Encoding());
}

std::wstring::const_iterator prevCharacter(std::wstring::const_iterator& first,
                                          std::wstring::const_iterator& last,
                                          size_t n)
{
    return Generic::prevCharacter(makeRange(first, last), n,
                                  Utf16Encoding());
}

std::wstring replace(const std::wstring& str,
                    const std::wstring& cmp,
                    const std::wstring& repl,
                    ptrdiff_t maxReplacements,
                    FindFlags_t flags)
{
    return Generic::replace<std::wstring>(makeRange(str), makeRange(cmp),
                                         makeRange(repl), Utf16Encoding(),
                                         maxReplacements, flags);
}

std::wstring replace(const std::wstring& str,
                    ptrdiff_t start,
                    ptrdiff_t end,
                    const std::wstring& repl)
{
    return Generic::replace<std::wstring>(makeRange(str), start, end,
                                         makeRange(repl), Utf16Encoding());
}

std::wstring replaceCodePoint(const std::wstring& s,
                              uint32_t from,
                              uint32_t to,
                              ptrdiff_t maxReplacements)
{
   uint16_t fBuf[2];
   auto fIt = fBuf;
   auto fromSize = encodeUtf16(fIt, std::end(fBuf), from);
   uint16_t tBuf[2];
   auto tIt = tBuf;
   auto toSize = encodeUtf16(tIt, std::end(tBuf), to);
   return Generic::replace<std::wstring>(
           makeRange(s),
           makeRange(fBuf, fBuf + fromSize),
           makeRange(tBuf, tBuf + toSize),
           Utf16Encoding(),
           maxReplacements, FindFlags::DEFAULTS);
}

std::wstring replaceInvalidUtf16(const std::wstring& str, uint32_t chr)
{
   std::wstring result;
   result.reserve(str.size());
   auto first = str.begin();
   auto it = str.begin();
   while (it != str.end())
   {
       uint32_t cp;
       if (nextUtf16CodePoint(cp, it, str.end()) != DecoderResult::OK)
       {
           result.append(first, it);
           first = ++it;
           append(result, chr);
       }
   }
   result.append(first, str.end());
   return result;
}

std::wstring& replaceInvalidUtf16InPlace(std::wstring& str, uint16_t chr)
{
   assert(chr > 0);
   auto it = str.begin();
   while (it != str.end())
   {
       uint32_t cp;
       if (nextUtf16CodePoint(cp, it, str.end()) != DecoderResult::OK)
           *it++ = chr;
   }
   return str;
}

std::wstring reverse(const std::wstring& str)
{
    return Generic::reverse<std::wstring>(makeRange(str), Utf16Encoding());
}

std::vector<std::wstring> split(
        const std::wstring& str,
        ptrdiff_t maxSplits,
        SplitFlags_t flags)
{
    return Generic::split<std::wstring>(
            makeRange(str), Utf16Encoding(),
            maxSplits, flags);
}

std::vector<std::wstring> split(
        const std::wstring& str,
        const std::wstring& sep,
        ptrdiff_t maxSplits,
        SplitFlags_t flags)
{
  return Generic::split<std::wstring>(
          makeRange(str), makeRange(sep), Utf16Encoding(), maxSplits, flags);
}

std::vector<std::wstring> splitIf(
        const std::wstring& str,
        std::function<bool(uint32_t)> predicate,
        ptrdiff_t maxSplits,
        SplitFlags_t flags)
{
    return Generic::splitIf<std::wstring>(
            makeRange(str), Utf16Encoding(), predicate, maxSplits, flags);
}

std::vector<std::wstring> splitLines(
        const std::wstring& str,
        ptrdiff_t maxSplits,
        SplitFlags_t flags)
{
    return Generic::splitLines<std::wstring>(makeRange(str), Utf16Encoding(),
                                            maxSplits, flags);
}

bool startsWith(const std::wstring& str,
                const std::wstring& cmp,
                FindFlags_t flags)
{
    return Generic::startsWith(makeRange(str), makeRange(cmp),
                               Utf16Encoding(), flags);
}

std::wstring substring(const std::wstring& str,
                      ptrdiff_t start,
                      ptrdiff_t end)
{
    return Generic::substring<std::wstring>(makeRange(str), start, end,
                                           Utf16Encoding());
}

std::wstring title(const std::wstring& str)
{
    return Generic::title<std::wstring>(makeRange(str), Utf16Encoding());
}

std::wstring toUtf16(uint32_t chr)
{
    std::wstring s;
    append(s, chr);
    return s;
}

std::wstring toUtf16(const std::string& str, Encoding_t encoding)
{
    return toUtf16(str.data(), str.size(), encoding);
}

std::wstring toUtf16(const std::wstring& str, Encoding_t encoding)
{
    return toUtf16(str.data(), str.size(), encoding);
}

std::wstring toUtf16(const char* str, size_t length, Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::UTF_8:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf8::Utf8Encoding(),
                Utf16Encoding());
    case Encoding::CP_437:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                CodePage::Cp437Encoding(),
                Utf16Encoding());
    case Encoding::LATIN_1:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                CodePage::Latin1Encoding(),
                Utf16Encoding());
    case Encoding::WINDOWS_1252:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                CodePage::Windows1252Encoding(),
                Utf16Encoding());
    case Encoding::UTF_16_BE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf16::Utf16BEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_16_LE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf16::Utf16LEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_32_BE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf32::Utf32BEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_32_LE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf32::Utf32LEEncoding(),
                Utf16Encoding());
    default:
        YSTRING_THROW("toUtf16: unsupported encoding " +
                               std::to_string(int64_t(encoding)));
    }
}

std::wstring toUtf16(const uint16_t* str, size_t length, Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::UTF_16_BE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf16::Utf16BEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_16_LE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf16::Utf16LEEncoding(),
                Utf16Encoding());
    default:
        YSTRING_THROW("toUtf16: unsupported encoding " +
                               std::to_string(int64_t(encoding)));
    }
}

std::wstring toUtf16(const uint32_t* str, size_t length, Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::UTF_16_BE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf16::Utf16BEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_16_LE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf16::Utf16LEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_32_BE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf32::Utf32BEEncoding(),
                Utf16Encoding());
    case Encoding::UTF_32_LE:
        return Generic::convert<std::wstring>(
                makeRange(str, str + length),
                Utf32::Utf32LEEncoding(),
                Utf16Encoding());
    default:
        YSTRING_THROW("toUtf16: unsupported encoding " +
                               std::to_string(int64_t(encoding)));
    }
}

std::wstring toUtf16(const std::u16string& str, Encoding_t encoding)
{
    return toUtf16(str.data(), str.size(), encoding);
}

std::wstring toUtf16(const std::u32string& str, Encoding_t encoding)
{
    return toUtf16(str.data(), str.size(), encoding);
}

std::wstring toUtf16(const wchar_t* str, size_t length, Encoding_t encoding)
{
    return toUtf16(internal_char_type_cast(str), length, encoding);
}

std::wstring toUtf16(const char16_t* str, size_t length, Encoding_t encoding)
{
    return toUtf16(internal_char_type_cast(str), length, encoding);
}

std::wstring toUtf16(const char32_t* str, size_t length, Encoding_t encoding)
{
    return toUtf16(internal_char_type_cast(str), length, encoding);
}

std::wstring trim(const std::wstring& str)
{
    return fromRange<std::wstring>(Generic::trim(
            makeRange(str),
            Utf16Encoding(),
            Unicode::isWhitespace));
}

std::wstring trim(const std::wstring& str,
                 std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::wstring>(Generic::trim(
            makeRange(str),
            Utf16Encoding(),
            predicate));
}

std::wstring trimEnd(const std::wstring& str)
{
    return fromRange<std::wstring>(Generic::trimEnd(
            makeRange(str),
            Utf16Encoding(),
            Unicode::isWhitespace));
}

std::wstring trimEnd(const std::wstring& str,
                    std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::wstring>(Generic::trimEnd(
            makeRange(str),
            Utf16Encoding(),
            predicate));
}

std::wstring trimStart(const std::wstring& str)
{
    return fromRange<std::wstring>(Generic::trimStart(
            makeRange(str),
            Utf16Encoding(),
            Unicode::isWhitespace));
}


std::wstring trimStart(const std::wstring& str,
                      std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::wstring>(Generic::trimStart(
            makeRange(str),
            Utf16Encoding(),
            predicate));
}

std::wstring unescape(const std::wstring& str, EscapeType_t type)
{
    return Generic::unescape<std::wstring>(
            makeRange(str),
            type,
            Utf16Encoding());
}

std::wstring upper(const std::wstring& str)
{
    return Generic::upper<std::wstring>(makeRange(str), Utf16Encoding());
}

}}
