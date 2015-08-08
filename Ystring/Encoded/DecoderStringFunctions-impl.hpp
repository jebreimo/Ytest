//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-03
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Unicode/CaseConverter.hpp"
#include "../Unicode/CaseInsensitive.hpp"
#include "../Unicode/UnicodePredicates.hpp"
#include "DecoderAlgorithms.hpp"

namespace Ystring { namespace Encoded {

template <typename Decoder>
bool advanceCharacter(Decoder& it)
{
    uint32_t ch;
    if (!it.next(ch))
        return false;
    auto prevIt = it.getLogicalBegin();
    if (Decoder::isForward)
    {
        while (it.next(ch))
        {
            if (!Unicode::isMark(ch))
            {
                it.setLogicalBegin(prevIt);
                break;
            }
            prevIt = it.getLogicalBegin();
        }
    }
    else
    {
        while (Unicode::isMark(ch) && it.next(ch))
        {}
    }
    return true;
}

template <typename Decoder>
size_t advanceCharacters(Decoder& it, size_t n)
{
    for (size_t i = 0; i != n; ++i)
    {
        if (!advanceCharacter(it))
            return i;
    }
    return n;
}

template <typename Encoder, typename Decoder>
void append(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(ch);
}

template <typename Encoder, typename Decoder>
void appendBytes(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encodeAsBytes(ch);
}

template <typename Encoder, typename Decoder>
void appendLower(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(Unicode::lower(ch));
}

template <typename Encoder, typename Decoder>
void appendTitle(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    bool capNext = true;
    while (src.next(ch))
    {
        if (!Unicode::isCasedLetter(ch))
        {
            dst.encode(ch);
            capNext = !Unicode::isLetter(ch);
        }
        else if (capNext)
        {
            dst.encode(Unicode::title(ch));
            capNext = false;
        }
        else
        {
            dst.encode(Unicode::lower(ch));
        }
    }
}

template <typename Encoder, typename Decoder>
void appendUpper(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(Unicode::upper(ch));
}

template <typename Decoder1, typename Decoder2>
int32_t caseInsensitiveCompare(Decoder1 str, Decoder2 cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    if (str.begin() == str.end() && cmp.begin() == cmp.end())
        return 0;
    else if (str.begin() == str.end())
        return -1;
    else if (cmp.begin() == cmp.end())
        return 1;
    uint32_t strCh, cmpCh;
    str.next(strCh);
    cmp.next(cmpCh);
    return Unicode::caseInsensitiveCompare(strCh, cmpCh);
}

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveEqual(Decoder1 str, Decoder2 cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    return str.begin() == str.end() && cmp.begin() == cmp.end();
}

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveLess(Decoder1 str, Decoder2 cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    if (str.begin() == str.end() || cmp.begin() == cmp.end())
        return str.begin() == str.end() && cmp.begin() != cmp.end();
    uint32_t strCh, cmpCh;
    str.next(strCh);
    cmp.next(cmpCh);
    return Unicode::caseInsensitiveLess(strCh, cmpCh);
}

template <typename Decoder1, typename Decoder2>
Decoder1 find(Decoder1& str, Decoder2 sub, FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return search(str, sub, Unicode::CaseInsensitiveEqual());
    else
        return search(str, sub);
}

template <typename Decoder>
bool isAlphaNumeric(Decoder dec)
{
    uint32_t ch;
    if (!dec.next(ch) || !Unicode::isAlphaNumeric(ch))
        return false;

    while (dec.next(ch))
    {
        if (!Unicode::isAlphaNumeric(ch) && !Unicode::isMark(ch))
            return false;
    }
    return true;
}

template <typename Decoder>
Decoder nextLine(Decoder& str)
{
    auto line = str;
    auto newline = nextNewline(str);
    line.setLogicalEnd(newline.getLogicalBegin());
    return line;
}

template <typename Decoder>
Decoder nextNewline(Decoder& str)
{
    auto newline = str;
    uint32_t ch;
    while (str.next(ch))
    {
        switch (ch)
        {
        case '\n':
            if (!Decoder::isForward)
            {
                auto copyOfStr = str;
                if (str.next(ch) && ch != '\r')
                    str.setLogicalBegin(copyOfStr.getLogicalBegin());
            }
            newline.setLogicalEnd(str.getLogicalBegin());
            return newline;
        case '\v':
        case '\f':
        case Unicode::NEXT_LINE:
        case Unicode::LINE_SEPARATOR:
        case Unicode::PARAGRAPH_SEPARATOR:
            newline.setLogicalEnd(str.getLogicalBegin());
            return newline;
        case '\r':
            if (Decoder::isForward)
            {
                auto copyOfStr = str;
                if (str.next(ch) && ch != '\n')
                    str.setLogicalBegin(copyOfStr.getLogicalBegin());
            }
            newline.setLogicalEnd(str.getLogicalBegin());
            return newline;
        default:
            break;
        }
        newline.setLogicalBegin(str.getLogicalBegin());
    }
    return str;
}

template <typename Decoder, typename UnaryPredicate>
Decoder nextToken(Decoder& str, UnaryPredicate predicate)
{
    auto token = str;
    token.setLogicalEnd(str.getLogicalBegin());
    uint32_t ch;
    while (str.next(ch) && !predicate(ch))
        token.setLogicalEnd(str.getLogicalBegin());
    return token;
}

template <typename Decoder1, typename Decoder2>
Decoder1 nextToken(Decoder1& str, Decoder2 cmp, FindFlags_t flags)
{
    auto token = str;
    auto delimiter = Encoded::find(str, cmp, flags);
    token.setLogicalEnd(delimiter.getLogicalBegin());
    return token;
}

template <typename Decoder1, typename Decoder2>
bool startsWith(Decoder1&& str, Decoder2&& cmp, FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    else
        advanceWhileEqual(str, cmp);
    return cmp.begin() == cmp.end();
}

}}
