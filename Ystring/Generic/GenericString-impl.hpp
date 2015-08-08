//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoded/AppendEscaped.hpp"
#include "../Encoded/AppendUnescaped.hpp"
#include "../Encoded/BackslashUnescaper.hpp"
#include "../Encoded/DecoderStringFunctions.hpp"
#include "../Encoded/Encoder.hpp"
#include "../Encoded/FixedLengthBackslashEscaper.hpp"
#include "../Encoded/ForwardDecoder.hpp"
#include "../Encoded/ReverseDecoder.hpp"
#include "../Encoded/VariableLengthBackslashEscaper.hpp"
#include "../Encoded/XmlEscaper.hpp"
#include "../Utilities/CountingOutputIterator.hpp"
#include "StringTypeTraits.hpp"

namespace Ystring { namespace Generic {

namespace Detail
{
    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendImpl(StringReference<Str> dst, Range<It> src,
                    Enc1 dstEncoding, Enc2 srcEncoding,
                    std::true_type);

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendImpl(StringReference<Str> dst, Range<It> src,
                    Enc1 dstEncoding, Enc2 srcEncoding,
                    std::false_type);

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendWithEncoder(StringReference<Str> dst, Range<It> src,
                           Enc1 dstEncoding, Enc2 srcEncoding,
                           std::true_type);

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendWithEncoder(StringReference<Str> dst, Range<It> src,
                           Enc1 dstEncoding, Enc2 srcEncoding,
                           std::false_type);

    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Range<It1> str,
                      Range<It2> cmp,
                      Enc /*encoding*/,
                      FindFlags_t /*flags*/,
                      std::true_type);

    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Range<It1> str,
                      Range<It2> cmp,
                      Enc encoding,
                      FindFlags_t flags,
                      std::false_type);

    template <typename It1, typename It2, typename Enc>
    Range<It1> findFirstImpl(Range<It1> str,
                             Range<It2> cmp,
                             Enc /*encoding*/,
                             FindFlags_t /*flags*/,
                             std::true_type);

    template <typename It1, typename It2, typename Enc>
    Range<It1> findFirstImpl(Range<It1> str,
                             Range<It2> cmp,
                             Enc encoding,
                             FindFlags_t flags,
                             std::false_type);

    template <typename It1, typename It2, typename Enc>
    Range<It1> findLastImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc /*encoding*/,
                            FindFlags_t /*flags*/,
                            std::true_type);

    template <typename It1, typename It2, typename Enc>
    Range<It1> findLastImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc encoding,
                            FindFlags_t flags,
                            std::false_type);

    template <typename It1, typename It2, typename Enc>
    std::vector<Range<It1>> findPositionsFwd(Range<It1> str, Range<It2> cmp,
                                             Enc encoding,
                                             size_t maxCount,
                                             FindFlags_t flags);

    template <typename It1, typename It2, typename Enc>
    std::vector<Range<It1>> findPositionsRev(Range<It1> str, Range<It2> cmp,
                                             Enc encoding,
                                             size_t maxCount,
                                             FindFlags_t flags);

    Encoded::FixedLengthBackslashEscaper makeFixedLengthBackslashEscaper(
            size_t charSize);

    template <typename Str, typename It1, typename It2, typename Enc>
    Str replaceFwd(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                   Enc encoding,
                   size_t maxReplacements,
                   FindFlags_t flags);

    template <typename Str, typename It1, typename It2, typename Enc>
    Str replaceRev(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                   Enc encoding,
                   size_t maxReplacements,
                   FindFlags_t flags);

    template <typename Str, typename Decoder, typename NextTokenFunc>
    std::vector<Str> splitImpl(
            Decoder str,
            NextTokenFunc nextTokenFunc,
            size_t maxSplits,
            SplitFlags_t flags);

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(
            Range<It1> str,
            Range<It2> cmp,
            Enc encoding,
            ptrdiff_t maxSplits,
            SplitFlags_t flags,
            std::true_type);

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(
            Range<It1> str,
            Range<It2> cmp,
            Enc encoding,
            ptrdiff_t maxSplits,
            SplitFlags_t flags,
            std::false_type);

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Range<It1> str,
                        Range<It2> cmp,
                        Enc /*encoding*/,
                        FindFlags_t /*flags*/,
                        std::true_type);

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Range<It1> str,
                        Range<It2> cmp,
                        Enc encoding,
                        FindFlags_t flags,
                        std::false_type);
}

template <typename Str, typename Enc>
void append(StringReference<Str>& dst, uint32_t chr, Enc encoding)
{
    auto encoder = dst.getEncoder(encoding);
    encoder.encode(chr);
}

template <typename Str, typename Enc>
void append(StringReference<Str>&& dst, uint32_t chr, Enc encoding)
{
    append(dst, chr, encoding);
}

template <typename Str, typename It, typename Enc1, typename Enc2>
void append(StringReference<Str> dst, Range<It> src,
            Enc1 dstEncoding, Enc2 srcEncoding)
{
    Detail::appendImpl(
            dst, src, dstEncoding, srcEncoding,
            CanCopyRawValues<typename StringReference<Str>::ValueType, Enc1,
                             typename Range<It>::ValueType, Enc2>());
}

template <typename Str, typename It, typename Enc>
void appendEscaped(StringReference<Str>& dst,
                   Range<It> src,
                   EscapeType_t type,
                   Enc encoding)
{
    typedef typename StringReference<Str>::ValueType Char;
    switch (type)
    {
    case EscapeType::BACKSLASH:
        Encoded::appendEscaped(
                dst.getAppender(),
                src,
                Encoded::isMandatoryEscape,
                Detail::makeFixedLengthBackslashEscaper(sizeof(Char)));
        break;
    case EscapeType::BACKSLASH_ASCII:
        Encoded::appendEscaped(
                dst.getAppender(),
                src,
                Encoded::isNonAsciiEscape,
                Detail::makeFixedLengthBackslashEscaper(sizeof(Char)));
        break;
    case EscapeType::BACKSLASH_ASCII_SMART:
        Encoded::appendEscaped(
                dst.getAppender(),
                Encoded::makeForwardDecoder(src, encoding),
                Encoded::isNonAsciiEscape,
                Encoded::VariableLengthBackslashEscaper());
        break;
    case EscapeType::JSON:
        Encoded::appendEscaped(
                dst.getAppender(),
                Encoded::makeForwardDecoder(src, encoding),
                Encoded::isMandatoryEscape,
                Encoded::FixedLengthBackslashEscaper('u', 4));
        break;
    case EscapeType::JSON_ASCII:
        Encoded::appendEscaped(
                dst.getAppender(),
                Encoded::makeForwardDecoder(src, encoding),
                Encoded::isNonAsciiEscape,
                Encoded::FixedLengthBackslashEscaper('u', 4));
        break;
    case EscapeType::XML_ATTRIBUTE:
        Encoded::appendEscaped(
                dst.getAppender(),
                Encoded::makeForwardDecoder(src, encoding),
                Encoded::isXmlAttributeEscape,
                Encoded::XmlEscaper());
        break;
    case EscapeType::XML_TEXT:
        Encoded::appendEscaped(
                dst.getAppender(),
                Encoded::makeForwardDecoder(src, encoding),
                Encoded::isXmlTextEscape,
                Encoded::XmlEscaper());
        break;
    default:
        YSTRING_THROW("Unsupported escape type " +
                               std::to_string(uint64_t(type)));
    }
}

template <typename Str, typename It1, typename It2>
void appendJoin(StringReference<Str>& dst, It1 first, It1 last,
                Range<It2> delimiter)
{
    if (first == last)
        return;

    auto appender = dst.getAppender();
    appender.append(makeRange(*first));
    while (++first != last)
    {
        appender.append(delimiter);
        appender.append(makeRange(*first));
    }
    dst.terminate();
}

template <typename Str, typename It>
void appendJoin(StringReference<Str>& dst, It first, It last)
{
    auto appender = dst.getAppender();
    for (; first != last; ++first)
        appender.append(makeRange(*first));
    dst.terminate();
}

template <typename Str, typename It, typename Enc>
void appendLower(StringReference<Str>& dst,
                 Range<It> src,
                 Enc encoding)
{
    Encoded::appendLower(
            dst.getEncoder(encoding),
            Encoded::makeForwardDecoder(src, encoding));
    dst.terminate();
}

template <typename Str, typename It, typename Enc>
void appendTitle(StringReference<Str>& dst,
                 Range<It> src,
                 Enc encoding)
{
    Encoded::appendTitle(
            dst.getEncoder(encoding),
            Encoded::makeForwardDecoder(src, encoding));
    dst.terminate();
}

template <typename Str, typename It, typename Enc>
void appendUnescaped(StringReference<Str>& dst,
                     Range<It> src,
                     EscapeType_t type,
                     Enc encoding)
{
    typedef typename StringReference<Str>::ValueType Char;
    switch (type)
    {
    case EscapeType::BACKSLASH:
    case EscapeType::BACKSLASH_ASCII:
    case EscapeType::BACKSLASH_ASCII_SMART:
        Encoded::appendUnescaped(
                dst,
                src,
                encoding,
                Encoded::isBackslash,
                Encoded::BackslashUnescaper(true));
        break;
    case EscapeType::JSON:
    case EscapeType::JSON_ASCII:
        Encoded::appendUnescaped(
                dst,
                src,
                encoding,
                Encoded::isBackslash,
                Encoded::BackslashUnescaper(false));
        break;
    case EscapeType::XML_ATTRIBUTE:
    case EscapeType::XML_TEXT:
    default:
        YSTRING_THROW("Unsupported escape type " +
                               std::to_string(uint64_t(type)));
    }
}

template <typename Str, typename It, typename Enc>
void appendUpper(StringReference<Str>& dst,
                 Range<It> src,
                 Enc encoding)
{
    Encoded::appendUpper(
            dst.getEncoder(encoding),
            Encoded::makeForwardDecoder(src, encoding));
    dst.terminate();
}

template <typename It1, typename It2, typename Enc>
int32_t caseInsensitiveCompare(Range<It1> str,
                               Range<It2> cmp,
                               Enc encoding)
{
    return caseInsensitiveCompare(
            Encoded::makeForwardDecoder(str, encoding),
            Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It1, typename It2, typename Enc>
bool caseInsensitiveEqual(Range<It1> str,
                          Range<It2> cmp,
                          Enc encoding)
{
    return caseInsensitiveEqual(Encoded::makeForwardDecoder(str, encoding),
                                Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It1, typename It2, typename Enc>
bool caseInsensitiveLess(Range<It1> str,
                         Range<It2> cmp,
                         Enc encoding)
{
    return caseInsensitiveLess(Encoded::makeForwardDecoder(str, encoding),
                               Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It, typename Enc>
bool contains(Range<It> str, uint32_t chr, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    return Encoded::advanceUntil(dec, [=](uint32_t c){return c == chr;});
}

template <typename Str, typename It, typename Enc1, typename Enc2>
Str convert(Range<It> str, Enc1 fromEncoding, Enc2 toEncoding)
{
    auto result = Str();
    append(makeStringReference(result), str, toEncoding, fromEncoding);
    return result;
}

template <typename It, typename Enc>
size_t countCharacters(Range<It> str, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    return advanceCharacters(dec, SIZE_MAX);
}

template <typename It, typename Enc>
size_t countCodePoints(Range<It> str, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    size_t n = 0;
    uint32_t ch;
    while (dec.next(ch))
        ++n;
    return n;
}

template <typename It1, typename It2, typename Enc>
bool endsWith(Range<It1> str,
              Range<It2> cmp,
              Enc encoding,
              FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Detail::endsWithImpl(str, cmp, encoding, flags,
                                    std::false_type());
    else
        return Detail::endsWithImpl(
                str, cmp, encoding, flags,
                SameIteratorValueType<It1, It2>());
}

template <typename Str, typename It, typename Enc>
Str escape(Range<It> src, EscapeType_t type, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendEscaped(ref, src, type, encoding);
    return str;
}

template <typename It1, typename It2, typename Enc>
Range<It1> findFirst(Range<It1> str,
                     Range<It2> cmp,
                     Enc encoding,
                     FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Detail::findFirstImpl(str, cmp, encoding, flags,
                                     std::false_type());
    else
        return Detail::findFirstImpl(
                str, cmp, encoding, flags,
                CanCompareRawValues<It1, Enc, It2, Enc>());
}

template <typename It, typename Enc>
Range<It> findFirstNewline(Range<It> str, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    return Encoded::nextNewline(dec).getRange();
}

template <typename It1, typename It2, typename Enc>
Range<It1> findLast(Range<It1> str,
                    Range<It2> cmp,
                    Enc encoding,
                    FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Detail::findLastImpl(str, cmp, encoding, flags,
                                    std::false_type());
    else
        return Detail::findLastImpl(
                str, cmp, encoding, flags,
                CanCompareRawValues<It1, Enc, It2, Enc>());
}

template <typename It, typename Enc>
Range<It> findLastNewline(Range<It> str, Enc encoding)
{
    auto dec = Encoded::makeReverseDecoder(str, encoding);
    return Encoded::nextNewline(dec).getRange();
}

template <typename It, typename Enc>
std::pair<Range<It>, Range<It>> findInsertPosition(Range<It> str,
                                                   ptrdiff_t pos,
                                                   Enc encoding)
{
    Range<It> range1 = str;
    Range<It> range2 = str;
    It insertPos;
    if (pos >= 0)
    {
        auto dec = Encoded::makeForwardDecoder(str, encoding);
        advanceCharacters(dec, static_cast<size_t>(pos));
        range1.end() = range2.begin() = dec.begin();
    }
    else
    {
        auto dec = Encoded::makeReverseDecoder(str, encoding);
        advanceCharacters(dec, static_cast<size_t>(-pos));
        range1.end() = range2.begin() = dec.end();
    }
    return std::make_pair(range1, range2);
}

template <typename Str, typename It1, typename It2, typename Enc>
Str insert(Range<It1> str, ptrdiff_t pos, Range<It2> sub, Enc encoding)
{
    auto ranges = findInsertPosition(str, pos, encoding);
    auto result = Str();
    auto ref = makeStringReference(result);
    auto appender = ref.getAppender();
    appender.append(ranges.first);
    appender.append(sub);
    appender.append(ranges.second);
    return result;
}

template <typename Str, typename It, typename Enc>
Str insert(Range<It> str, ptrdiff_t pos, uint32_t chr, Enc encoding)
{
    auto ranges = findInsertPosition(str, pos, encoding);
    auto result = Str();
    auto ref = makeStringReference(result);
    ref.getAppender().append(ranges.first);
    ref.getEncoder(encoding).encode(chr);
    ref.getAppender().append(ranges.second);
    return result;
}

template <typename It, typename Enc>
bool isAlphaNumeric(Range<It> str, Enc encoding)
{
    return isAlphaNumeric(Encoded::makeForwardDecoder(str, encoding));
}

template <typename Str, typename It1, typename It2>
Str join(It1 first, It1 last, Range<It2> delimiter)
{
    auto result = Str();
    auto ref = makeStringReference(result);
    appendJoin(ref, first, last, delimiter);
    return result;
}

template <typename Str, typename It>
Str join(It first, It last)
{
    auto result = Str();
    auto ref = makeStringReference(result);
    appendJoin(ref, first, last);
    return result;
}

template <typename Str, typename It, typename Enc>
Str lower(Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendLower(ref, src, encoding);
    return str;
}

template <typename It, typename Enc>
It nextCharacter(Range<It> str, size_t n, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    if (advanceCharacters(dec, n) != n)
      YSTRING_THROW(
              "can't advance beyond the end of the range");
    return dec.begin();
}

template <typename It, typename Enc>
It nthCharacter(Range<It> str, ptrdiff_t n, Enc encoding)
{
    if (n >= 0)
        return nextCharacter(str, static_cast<size_t>(n), encoding);
    else
        return prevCharacter(str, static_cast<size_t>(-n), encoding);
}

template <typename It, typename Enc>
It prevCharacter(Range<It> str, size_t n, Enc encoding)
{
    auto dec = Encoded::makeReverseDecoder(str, encoding);
    if (advanceCharacters(dec, n) != n)
      YSTRING_THROW(
              "can't advance beyond the start of the range");
    return dec.end();
}

template <typename It1, typename It2, typename Enc>
std::vector<Range<It1>> findPositions(Range<It1> str, Range<It2> cmp,
                                      Enc encoding,
                                      ptrdiff_t maxCount,
                                      FindFlags_t flags)
{
    if (maxCount >= 0)
        return Detail::findPositionsFwd(
                str, cmp, encoding, static_cast<size_t>(maxCount), flags);
    else
        return Detail::findPositionsRev(
                str, cmp, encoding, static_cast<size_t>(-maxCount), flags);
}

template <typename Str, typename It1, typename It2, typename Enc>
Str replace(Range<It1> str, Range<It2> cmp, Range<It2> rep,
            Enc encoding,
            ptrdiff_t maxReplacements,
            FindFlags_t flags)
{
    if (cmp.begin() == cmp.end())
        return Str(str.begin(), str.end());

    if (maxReplacements >= 0)
        return Detail::replaceFwd<Str>(
                str, cmp, rep, encoding,
                static_cast<size_t>(maxReplacements), flags);
    else
        return Detail::replaceRev<Str>(
                str, cmp, rep, encoding,
                static_cast<size_t>(-maxReplacements), flags);
}

template <typename Str, typename It1, typename It2, typename Enc>
Str replace(Range<It1> str, ptrdiff_t start, ptrdiff_t end, Range<It2> rep,
            Enc encoding)
{
    auto sub = subrange(str, start, end, encoding);
    auto result = Str();
    auto ref = makeStringReference(result);
    auto appender = ref.getAppender();
    appender.append(makeRange(str.begin(), sub.begin()));
    appender.append(rep);
    appender.append(makeRange(sub.end(), str.end()));
    return result;
}

template <typename Str, typename It, typename Enc>
Str reverse(Range<It> src, Enc encoding)
{
    Str result(getSize(src), 0);
    auto dst = begin(result);
    auto dec = Encoded::makeReverseDecoder(src, encoding);
    while (advanceCharacter(dec))
    {
        src.begin() = dec.end();
        dst = copy(src, dst);
        src.end() = src.begin();
    }
    return result;
}

template <typename It1, typename It2>
size_t sizeOfJoin(It1 first, It1 last, Range<It2> delimiter)
{
    size_t n = 0, len = 0;
    for (; first != last; ++first)
    {
        len += getSize(makeRange(*first));
        ++n;
    }
    return len + (n - 1) * getSize(delimiter);
}

template <typename It>
size_t sizeOfJoin(It first, It last)
{
    size_t size = 0;
    for (; first != last; ++first)
        size += getSize(makeRange(first));
    return size;
}

template <typename It, typename Enc>
size_t sizeOfLower(Range<It> src, Enc encoding)
{
    size_t n = 0;
    Utilities::CountingOutputIterator<typename Enc::CanonicalType> it(&n);
    Encoded::appendLower(
            Encoded::makeEncoder(it, encoding),
            Encoded::makeForwardDecoder(src, encoding));
    return n;
}

template <typename It, typename Enc>
size_t sizeOfUpper(Range<It> src, Enc encoding)
{
    size_t n = 0;
    Utilities::CountingOutputIterator<typename Enc::CanonicalType> it(&n);
    Encoded::appendUpper(
            Encoded::makeEncoder(it, encoding),
            Encoded::makeForwardDecoder(src, encoding));
    return n;
}

template <typename Str, typename It, typename Enc>
std::vector<Str> split(Range<It> str,
                       Enc encoding,
                       ptrdiff_t maxSplits,
                       SplitFlags_t flags)
{
    return splitIf<Str>(str, encoding, Unicode::isWhitespace,
                        maxSplits, flags);
}

template <typename Str, typename It1, typename It2, typename Enc>
std::vector<Str> split(Range<It1> str,
                       Range<It2> cmp,
                       Enc encoding,
                       ptrdiff_t maxSplits,
                       SplitFlags_t flags)
{
    if (SplitFlags::isCaseInsensitive(flags) || maxSplits < 0)
        return Detail::splitImpl<Str>(str, cmp, encoding, maxSplits, flags,
                                      std::false_type());
    else
        return Detail::splitImpl<Str>(str, cmp, encoding, maxSplits, flags,
                                      SameIteratorValueType<It1, It2>());
}

template <typename Str, typename It, typename Enc, typename Predicate>
std::vector<Str> splitIf(Range<It> str,
                         Enc encoding,
                         Predicate predicate,
                         ptrdiff_t maxSplits,
                         SplitFlags_t flags)
{
    if (maxSplits >= 0)
        return Detail::splitImpl<Str>(
                Encoded::makeForwardDecoder(str, encoding),
                [&](Encoded::ForwardDecoder<It, Enc>& d)
                   {return nextToken(d, predicate);},
                maxSplits, flags);
    else
        return Detail::splitImpl<Str>(
                Encoded::makeReverseDecoder(str, encoding),
                [&](Encoded::ReverseDecoder<It, Enc>& d)
                   {return nextToken(d, predicate);},
                -maxSplits, flags);
}

template <typename Str, typename It, typename Enc>
std::vector<Str> splitLines(Range<It> str,
                            Enc encoding,
                            ptrdiff_t maxSplits,
                            SplitFlags_t flags)
{
    if (maxSplits >= 0)
        return Detail::splitImpl<Str>(
                Encoded::makeForwardDecoder(str, encoding),
                [&](Encoded::ForwardDecoder<It, Enc>& d)
                   {return nextLine(d);},
                maxSplits, flags);
    else
        return Detail::splitImpl<Str>(
                Encoded::makeReverseDecoder(str, encoding),
                [&](Encoded::ReverseDecoder<It, Enc>& d)
                   {return nextLine(d);},
                -maxSplits, flags);
}

template <typename It1, typename It2, typename Enc>
bool startsWith(Range<It1> str,
                Range<It2> cmp,
                Enc encoding,
                FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Detail::startsWithImpl(str, cmp, encoding, flags,
                                      std::false_type());
    else
        return Detail::startsWithImpl(
                str, cmp, encoding, flags,
                SameIteratorValueType<It1, It2>());
}

template <typename It, typename Enc>
Range<It> subrange(Range<It> str, ptrdiff_t start, ptrdiff_t end,
                   Enc encoding)
{
    if (end == PTRDIFF_MAX)
        return makeRange(nthCharacter(str, start, encoding), str.end());

    It first, last;
    auto sameSign = start >= 0 == end >= 0;
    if (sameSign)
    {
        if (start >= end)
        {
            first = nthCharacter(str, start, encoding);
            last = first;
        }
        else if (start >= 0)
        {
            first = nthCharacter(str, start, encoding);
            last = nthCharacter(makeRange(first, str.end()), end - start,
                                 encoding);
        }
        else
        {
            last = nthCharacter(str, end, encoding);
            first = nthCharacter(makeRange(str.begin(), last), start - end,
                                 encoding);
        }
    }
    else
    {
        first = nthCharacter(str, start, encoding);
        last = nthCharacter(str, end, encoding);
        using std::distance;
        if (distance(str.begin(), first) > distance(str.begin(), last))
        {
            last = first;
        }
    }

    return Range<It>(first, last);
}

template <typename Str, typename It, typename Enc>
Str substring(Range<It> str, ptrdiff_t start, ptrdiff_t end, Enc encoding)
{
    auto sub = subrange(str, start, end, encoding);
    return Str(sub.begin(), sub.end());
}

template <typename Str, typename It, typename Enc>
Str title(Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendTitle(ref, src, encoding);
    return str;
}

template <typename It, typename Enc, typename UnaryPred>
Range<It> trim(Range<It> str,
               Enc encoding,
               UnaryPred trimChar)
{
    return trimEnd(trimStart(str, encoding, trimChar), encoding, trimChar);
}

template <typename It, typename Enc, typename UnaryPred>
Range<It> trimEnd(Range<It> str,
                  Enc encoding,
                  UnaryPred trimChar)
{
    auto dec = Encoded::makeReverseDecoder(str, encoding);
    advanceWhile(dec, trimChar);
    return dec.getRange();
}

template <typename It, typename Enc, typename UnaryPred>
Range<It> trimStart(Range<It> str,
                    Enc encoding,
                    UnaryPred trimChar)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    advanceWhile(dec, trimChar);
    return dec.getRange();
}

template <typename Str, typename It, typename Enc>
Str unescape(Range<It> src, EscapeType_t type, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendUnescaped(ref, src, type, encoding);
    return str;
}

template <typename Str, typename It, typename Enc>
Str upper(Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendUpper(ref, src, encoding);
    return str;
}

namespace Detail
{
    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendImpl(StringReference<Str> dst, Range<It> src,
                    Enc1 dstEncoding, Enc2 srcEncoding,
                    std::true_type)
    {
        auto appender = dst.getAppender();
        appender.append(src);
        dst.terminate();
    }

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendImpl(StringReference<Str> dst, Range<It> src,
                    Enc1 dstEncoding, Enc2 srcEncoding,
                    std::false_type)
    {
        appendWithEncoder(dst, src, dstEncoding, srcEncoding,
                          IsByteString<Str>());
        dst.terminate();
    }

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendWithEncoder(StringReference<Str> dst, Range<It> src,
                           Enc1 dstEncoding, Enc2 srcEncoding,
                           std::true_type)
    {
        appendBytes(dst.getEncoder(dstEncoding),
                    Encoded::makeForwardDecoder(src, srcEncoding));
        dst.terminate();
    }

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void appendWithEncoder(StringReference<Str> dst, Range<It> src,
                           Enc1 dstEncoding, Enc2 srcEncoding,
                           std::false_type)
    {
        append(dst.getEncoder(dstEncoding),
               Encoded::makeForwardDecoder(src, srcEncoding));
        dst.terminate();
    }

    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Range<It1> str,
                      Range<It2> cmp,
                      Enc /*encoding*/,
                      FindFlags_t /*flags*/,
                      std::true_type)
    {
        auto strRange = makeReverseRange(str);
        auto cmpRange = makeReverseRange(cmp);
        return mismatch(strRange, cmpRange).second == cmpRange.end();
    }

    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Range<It1> str,
                      Range<It2> cmp,
                      Enc encoding,
                      FindFlags_t flags,
                      std::false_type)
    {
        return Encoded::startsWith(Encoded::makeReverseDecoder(str, encoding),
                                   Encoded::makeReverseDecoder(cmp, encoding),
                                   flags);
    }

    template <typename It1, typename It2, typename Enc>
    Range<It1> findFirstImpl(Range<It1> str,
                             Range<It2> cmp,
                             Enc /*encoding*/,
                             FindFlags_t /*flags*/,
                             std::true_type)
    {
        return search(str, cmp);
    }

    template <typename It1, typename It2, typename Enc>
    Range<It1> findFirstImpl(Range<It1> str,
                             Range<It2> cmp,
                             Enc encoding,
                             FindFlags_t flags,
                             std::false_type)
    {
        auto strDec = Encoded::makeForwardDecoder(str, encoding);
        return Encoded::find(strDec,
                             Encoded::makeForwardDecoder(cmp, encoding),
                             flags).getRange();
    }

    template <typename It1, typename It2, typename Enc>
    Range<It1> findLastImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc /*encoding*/,
                            FindFlags_t /*flags*/,
                            std::true_type)
    {
        return searchLast(str, cmp);
    }

    template <typename It1, typename It2, typename Enc>
    Range<It1> findLastImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc encoding,
                            FindFlags_t flags,
                            std::false_type)
    {
        auto strDec = Encoded::makeReverseDecoder(str, encoding);
        return Encoded::find(strDec,
                             Encoded::makeReverseDecoder(cmp, encoding),
                             flags).getRange();
    }

    template <typename It1, typename It2, typename Enc>
    std::vector<Range<It1>> findPositionsFwd(Range<It1> str, Range<It2> cmp,
                                             Enc encoding,
                                             size_t maxCount,
                                             FindFlags_t flags)
    {
        std::vector<Range<It1>> result;
        auto nxt = findFirst(str, cmp, encoding, flags);
        while (nxt.begin() != nxt.end())
        {
            result.push_back(nxt);
            if (--maxCount == 0)
                break;
            str.begin() = nxt.end();
            nxt = findFirst(str, cmp, encoding, flags);
        }
        return result;
    }

    template <typename It1, typename It2, typename Enc>
    std::vector<Range<It1>> findPositionsRev(Range<It1> str, Range<It2> cmp,
                                             Enc encoding,
                                             size_t maxCount,
                                             FindFlags_t flags)
    {
        std::vector<Range<It1>> result;
        auto prv = findLast(str, cmp, encoding, flags);
        while (prv.begin() != prv.end())
        {
            result.push_back(prv);
            if (--maxCount == 0)
                break;
            str.end() = prv.begin();
            prv = findLast(str, cmp, encoding, flags);
        }
        return result;
    }

    inline
    Encoded::FixedLengthBackslashEscaper makeFixedLengthBackslashEscaper(
            size_t charSize)
    {
        if (charSize == 1)
            return Encoded::FixedLengthBackslashEscaper('x', 2);
        if (charSize == 2)
            return Encoded::FixedLengthBackslashEscaper('u', 4);
        return Encoded::FixedLengthBackslashEscaper('U', 8);
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    Str replaceFwd(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                   Enc encoding,
                   size_t maxReplacements,
                   FindFlags_t flags)
    {
        auto result = Str();
        auto ref = makeStringReference(result);
        auto appender = ref.getAppender();
        auto sub = findFirst(str, cmp, encoding, flags);
        while (sub.begin() != sub.end())
        {
            appender.append(makeRange(str.begin(), sub.begin()));
            appender.append(rep);
            str.begin() = sub.end();
            if (--maxReplacements == 0)
                break;
            sub = findFirst(str, cmp, encoding, flags);
        }
        appender.append(str);
        return result;
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    Str replaceRev(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                   Enc encoding,
                   size_t maxReplacements,
                   FindFlags_t flags)
    {
        auto positions = findPositionsRev(str, cmp, encoding,
                                          maxReplacements, flags);
        auto result = Str();
        auto ref = makeStringReference(result);
        auto appender = ref.getAppender();
        for (auto it = positions.rbegin(); it != positions.rend(); ++it)
        {
            appender.append(makeRange(str.begin(), it->begin()));
            appender.append(rep);
            str.begin() = it->end();
        }
        appender.append(str);
        return result;
    }

    template <typename Decoder, typename NextTokenFunc>
    Decoder nextNonEmptyToken(Decoder& str, NextTokenFunc nextTokenFunc)
    {
        while (!empty(str))
        {
            auto token = nextTokenFunc(str);
            if (!empty(token))
                return token;
        }
        return str;
    }

    template <typename Str, typename Decoder, typename NextTokenFunc>
    std::vector<Str> splitImpl(Decoder str,
                               NextTokenFunc nextTokenFunc,
                               size_t maxSplits,
                               SplitFlags_t flags)
    {
        std::vector<Str> result;
        if (maxSplits == 0)
            --maxSplits;

        auto token = nextTokenFunc(str);
        if (!SplitFlags::ignoreEmptyFront(flags) || !empty(token))
        {
            result.emplace_back(token.begin(), token.end());
            --maxSplits;
        }
        if (token.end() == str.end())
            return result;

        while (maxSplits != 0 && !empty(str))
        {
            token = SplitFlags::ignoreEmptyIntermediates(flags)
                  ? nextNonEmptyToken(str, nextTokenFunc)
                  : nextTokenFunc(str);
            if (token.end() == str.end())
            {
                str = token;
                break;
            }
            result.emplace_back(token.begin(), token.end());
            --maxSplits;
        }

        if (SplitFlags::ignoreEmptyIntermediates(flags) && maxSplits == 0)
        {
            token = nextNonEmptyToken(str, nextTokenFunc);
            str.setLogicalBegin(token.getLogicalBegin());
        }
        if ((!SplitFlags::ignoreRemainder(flags)) &&
            (!SplitFlags::ignoreEmptyBack(flags) || !empty(str)))
        {
            result.emplace_back(str.begin(), str.end());
        }
        return result;
    }

    template <typename It1, typename It2>
    Range<It1> nextToken(Range<It1>& str, Range<It2> cmp)
    {
        auto sep = search(str, cmp);
        auto token = !empty(sep) ? makeRange(str.begin(), sep.begin())
                                 : str;
        str.begin() = sep.end();
        return token;
    }

    template <typename It1, typename It2>
    Range<It1> nextNonEmptyToken(Range<It1>& str, Range<It2> cmp)
    {
        while (!empty(str))
        {
            auto token = nextToken(str, cmp);
            if (!empty(token))
                return token;
        }
        return str;
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(Range<It1> str,
                               Range<It2> cmp,
                               Enc /*encoding*/,
                               ptrdiff_t maxSplits,
                               SplitFlags_t flags,
                               std::true_type)
    {
        std::vector<Str> result;
        if (maxSplits == 0)
            --maxSplits;

        auto token = nextToken(str, cmp);
        if (!SplitFlags::ignoreEmptyFront(flags) || !empty(token))
        {
            result.emplace_back(token.begin(), token.end());
            --maxSplits;
        }
        if (token.end() == str.end())
            return result;

        while (maxSplits != 0 && !empty(str))
        {
            token = SplitFlags::ignoreEmptyIntermediates(flags)
                  ? nextNonEmptyToken(str, cmp)
                  : nextToken(str, cmp);
            if (token.end() == str.end())
            {
                str = token;
                break;
            }
            result.emplace_back(token.begin(), token.end());
            --maxSplits;
        }

        if (SplitFlags::ignoreEmptyIntermediates(flags) && maxSplits == 0)
        {
            token = nextNonEmptyToken(str, cmp);
            str.begin() = token.begin();
        }
        if ((!SplitFlags::ignoreRemainder(flags)) &&
            (!SplitFlags::ignoreEmptyBack(flags) || !empty(str)))
        {
            result.emplace_back(str.begin(), str.end());
        }
//        if (maxSplits == 0)
//            --maxSplits;
//        std::vector<Str> result;
//        while (maxSplits != 0 && str.begin() != str.end())
//        {
//            auto token = search(str, cmp);
//            if (!SplitFlags::ignoreEmpty(flags) ||
//                str.begin() != token.begin())
//            {
//                result.emplace_back(str.begin(), token.begin());
//                --maxSplits;
//            }
//            if (token.end() == str.end())
////                return result;
//            str.begin() = token.end();
//        }
//        if ((!SplitFlags::ignoreRemainder(flags)) &&
//            (!SplitFlags::ignoreEmpty(flags) || str.begin() != str.end()))
//        {
//            result.emplace_back(str.begin(), str.end());
//        }
        return result;
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(Range<It1> str,
                               Range<It2> cmp,
                               Enc encoding,
                               ptrdiff_t maxSplits,
                               SplitFlags_t flags,
                               std::false_type)
    {
        auto findFlags = SplitFlags::toFindFlags(flags);
        if (maxSplits >= 0)
        {
            auto cmpDec = Encoded::makeForwardDecoder(cmp, encoding);
            return splitImpl<Str>(
                    Encoded::makeForwardDecoder(str, encoding),
                    [=](Encoded::ForwardDecoder<It1, Enc>& d)
                       {return nextToken(d, cmpDec, findFlags);},
                    size_t(maxSplits), flags);
        }
        else
        {
            auto cmpDec = Encoded::makeReverseDecoder(cmp, encoding);
            return splitImpl<Str>(
                    Encoded::makeReverseDecoder(str, encoding),
                    [=](Encoded::ReverseDecoder<It1, Enc>& d)
                       {return nextToken(d, cmpDec, findFlags);},
                    size_t(-maxSplits), flags);
        }
    }

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Range<It1> str,
                        Range<It2> cmp,
                        Enc /*encoding*/,
                        FindFlags_t /*flags*/,
                        std::true_type)
    {
        return mismatch(str, cmp).second == cmp.end();
    }

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Range<It1> str,
                        Range<It2> cmp,
                        Enc encoding,
                        FindFlags_t flags,
                        std::false_type)
    {
        return Encoded::startsWith(Encoded::makeForwardDecoder(str, encoding),
                                   Encoded::makeForwardDecoder(cmp, encoding),
                                   flags);
    }
}

}}
