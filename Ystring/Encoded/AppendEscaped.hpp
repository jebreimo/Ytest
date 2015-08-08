//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-16
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Generic/Range.hpp"
#include "ForwardDecoder.hpp"

namespace Ystring { namespace Encoded {

inline bool isMandatoryEscape(uint32_t c)
{
    return c < 32 || c == '"' || c == '\\' || (127 <= c && c < 160);
}

inline bool isNonAsciiEscape(uint32_t c)
{
    return c < 32 || c == '"' || c == '\\' || 127 <= c;
}

inline bool isXmlAttributeEscape(uint32_t c)
{
    return c < 32 || c == '"' || c == '&' || c == '\'' ||
           c == '<' || c == '>';
}

inline bool isXmlTextEscape(uint32_t c)
{
    return c == '&' || c == '<' || c == '>';
}

template <typename Appender, typename It, typename Escaper>
void appendEscaped(Appender dst, Generic::Range<It> src,
                   bool (*isEscapable)(uint32_t), Escaper escaper)
{
    typedef typename Generic::Range<It>::ValueType Char;
    typedef typename std::make_unsigned<Char>::type UChar;

    auto first = src.begin();
    auto predicate = [&](Char c){return isEscapable(UChar(c));};
    auto last = std::find_if(first, src.end(), predicate);
    while (last != src.end())
    {
        dst.append(Generic::makeRange(first, last));
        escaper.escape(dst, (UChar)*last);
        first = ++last;
        last = std::find_if(first, src.end(), predicate);
    }
    dst.append(Generic::makeRange(first, src.end()));
};

template <typename Appender, typename It, typename Enc, typename Escaper>
void appendEscaped(Appender dst, ForwardDecoder<It, Enc> src,
                   bool (*isEscapable)(uint32_t), Escaper escaper)
{
    auto first = src.begin();
    while (advanceUntil(src, isEscapable))
    {
        dst.append(Generic::makeRange(first, src.begin()));
        uint32_t c;
        src.next(c);
        escaper.escape(dst, c);
        first = src.begin();
    }
    dst.append(Generic::makeRange(first, src.begin()));
};

}}
