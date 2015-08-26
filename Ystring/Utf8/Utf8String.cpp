//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf8String.hpp"

#include "../PrivatePlatformDetails.hpp"
#include "../Generic/GenericString.hpp"
#include "../Utf16/Utf16Encoding.hpp"
#include "../Utf32/Utf32Encoding.hpp"
#include "Utf8Encoding.hpp"

namespace Ystring { namespace Utf8 {

using Generic::makeStringReference;
using Generic::makeRange;
using Generic::fromRange;

size_t countCharacters(const std::string& str)
{
    return Generic::countCharacters(makeRange(str), Utf8Encoding());
}

size_t countCharacters(std::string::const_iterator first,
                       std::string::const_iterator last)
{
    return Generic::countCharacters(makeRange(first, last), Utf8Encoding());
}

bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags)
{
    return Generic::endsWith(
            makeRange(str),
            makeRange(cmp),
            Utf8Encoding(),
            flags);
}

uint32_t getCodePoint(const std::string& str, ptrdiff_t n)
{
    return Generic::getCodePoint(makeRange(str), n, Utf8Encoding());
}

std::string join(const std::vector<std::string>& strings,
                 const std::string& delimiter)
{
    return join(strings.data(), strings.size(), delimiter);
}

std::string join(const std::string* strings,
                 size_t count,
                 const std::string& delimiter)
{
    return delimiter.empty() ?
           Generic::join<std::string>(strings, strings + count) :
           Generic::join<std::string>(strings, strings + count,
                                      makeRange(delimiter));
}

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        ptrdiff_t maxSplits,
        SplitFlags_t flags)
{
  return Generic::split<std::string>(
          makeRange(str), makeRange(sep), Utf8Encoding(), maxSplits, flags);
}

std::vector<std::string> splitIf(
        const std::string& str,
        std::function<bool(uint32_t)> predicate,
        ptrdiff_t maxSplits,
        SplitFlags_t flags)
{
    return Generic::splitIf<std::string>(
            makeRange(str), Utf8Encoding(), predicate, maxSplits, flags);
}

std::string toUtf8(const std::wstring& str, Encoding_t encoding)
{
    return toUtf8(str.data(), str.size(), encoding);
}

std::string toUtf8(const uint16_t* str, size_t length, Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::UTF_16_BE:
        return Generic::convert<std::string>(
                makeRange(str, str + length),
                Utf16::Utf16BEEncoding(),
                Utf8Encoding());
    case Encoding::UTF_16_LE:
        return Generic::convert<std::string>(
                makeRange(str, str + length),
                Utf16::Utf16LEEncoding(),
                Utf8Encoding());
    default:
        YSTRING_THROW("toUtf8: unsupported encoding " +
                               std::to_string(int64_t(encoding)));
    }
}

std::string toUtf8(const uint32_t* str, size_t length, Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::UTF_16_BE:
        return Generic::convert<std::string>(
                makeRange(str, str + length),
                Utf16::Utf16BEEncoding(),
                Utf8Encoding());
    case Encoding::UTF_16_LE:
        return Generic::convert<std::string>(
                makeRange(str, str + length),
                Utf16::Utf16LEEncoding(),
                Utf8Encoding());
    case Encoding::UTF_32_BE:
        return Generic::convert<std::string>(
                makeRange(str, str + length),
                Utf32::Utf32BEEncoding(),
                Utf8Encoding());
    case Encoding::UTF_32_LE:
        return Generic::convert<std::string>(
                makeRange(str, str + length),
                Utf32::Utf32LEEncoding(),
                Utf8Encoding());
    default:
        YSTRING_THROW("toUtf8: unsupported encoding " +
                               std::to_string(int64_t(encoding)));
    }
}

std::string toUtf8(const std::u16string& str, Encoding_t encoding)
{
    return toUtf8(str.data(), str.size(), encoding);
}

std::string toUtf8(const std::u32string& str, Encoding_t encoding)
{
    return toUtf8(str.data(), str.size(), encoding);
}

std::string toUtf8(const wchar_t* str, size_t length, Encoding_t encoding)
{
    return toUtf8(internal_char_type_cast(str), length, encoding);
}

#ifdef YSTRING_CPP11_CHAR_TYPES_SUPPORTED

std::string toUtf8(const char16_t* str, size_t length, Encoding_t encoding)
{
    return toUtf8(internal_char_type_cast(str), length, encoding);
}

std::string toUtf8(const char32_t* str, size_t length, Encoding_t encoding)
{
    return toUtf8(internal_char_type_cast(str), length, encoding);
}

#endif

std::string trim(const std::string& str)
{
    return fromRange<std::string>(Generic::trim(
            makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}

}}
