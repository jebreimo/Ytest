//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31.
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

namespace Ystring { namespace Utf8
{
    using Generic::makeStringReference;
    using Generic::makeRange;
    using Generic::fromRange;
    typedef std::string String;
    typedef Utf8Encoding Enc;

    size_t countCharacters(const String& str)
    {
        return Generic::countCharacters(makeRange(str), Enc());
    }

    size_t countCharacters(std::string::const_iterator first,
                           std::string::const_iterator last)
    {
        return Generic::countCharacters(makeRange(first, last), Enc());
    }

    bool endsWith(const String& str, const String& cmp, FindFlags_t flags)
    {
        return Generic::endsWith(
                makeRange(str), makeRange(cmp), Enc(), flags);
    }

    uint32_t getCodePoint(const String& str, ptrdiff_t n)
    {
        return Generic::getCodePoint(makeRange(str), n, Enc());
    }

    String join(const std::vector<String>& strings,
                const String& delimiter)
    {
        return join(strings.data(), strings.size(), delimiter);
    }

    String join(const String* strings, size_t count, const String& delimiter)
    {
        return delimiter.empty() ?
               Generic::join<String>(strings, strings + count) :
               Generic::join<String>(
                        strings, strings + count, makeRange(delimiter));
    }

    std::vector<String> split(const String& str,
                              const String& sep,
                              ptrdiff_t maxSplits,
                              SplitFlags_t flags)
    {
      return Generic::split<String>(
              makeRange(str), makeRange(sep), Enc(), maxSplits, flags);
    }

    std::vector<String> splitIf(const String& str,
                                std::function<bool(uint32_t)> predicate,
                                ptrdiff_t maxSplits,
                                SplitFlags_t flags)
    {
        return Generic::splitIf<String>(
                makeRange(str), Enc(), predicate, maxSplits, flags);
    }

    String toUtf8(const std::wstring& str, Encoding_t encoding)
    {
        return toUtf8(str.data(), str.size(), encoding);
    }

    #define CASE_ENCODING(enumName, encodingName) \
        case enumName: \
            return Generic::convert<String>( \
                    makeRange(str, str + length), \
                    encodingName(), \
                    Enc())

    String toUtf8(const uint16_t* str, size_t length, Encoding_t encoding)
    {
        switch (encoding)
        {
        CASE_ENCODING(Encoding::UTF_16_BE, Utf16::Utf16BEEncoding);
        CASE_ENCODING(Encoding::UTF_16_LE, Utf16::Utf16LEEncoding);
        default:
            YSTRING_THROW("toUtf8: unsupported encoding " +
                          std::to_string(int64_t(encoding)));
        }
    }

    String toUtf8(const uint32_t* str, size_t length, Encoding_t encoding)
    {
        switch (encoding)
        {
        CASE_ENCODING(Encoding::UTF_32_BE, Utf32::Utf32BEEncoding);
        CASE_ENCODING(Encoding::UTF_32_LE, Utf32::Utf32LEEncoding);
        default:
            YSTRING_THROW("toUtf8: unsupported encoding " +
                          std::to_string(int64_t(encoding)));
        }
    }

    String toUtf8(const std::u16string& str, Encoding_t encoding)
    {
        return toUtf8(str.data(), str.size(), encoding);
    }

    String toUtf8(const std::u32string& str, Encoding_t encoding)
    {
        return toUtf8(str.data(), str.size(), encoding);
    }

    String toUtf8(const wchar_t* str, size_t length, Encoding_t encoding)
    {
        return toUtf8(internal_char_type_cast(str), length, encoding);
    }

    #ifdef YSTRING_CPP11_CHAR_TYPES_SUPPORTED

    String toUtf8(const char16_t* str, size_t length, Encoding_t encoding)
    {
        return toUtf8(internal_char_type_cast(str), length, encoding);
    }

    String toUtf8(const char32_t* str, size_t length, Encoding_t encoding)
    {
        return toUtf8(internal_char_type_cast(str), length, encoding);
    }

    #endif

    String trim(const String& str)
    {
        return fromRange<String>(Generic::trim(
                makeRange(str), Enc(), Unicode::isWhitespace));
    }

}}
