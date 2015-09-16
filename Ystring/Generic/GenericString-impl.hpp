//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoded/DecoderStringFunctions.hpp"
#include "../Encoded/Encoder.hpp"
#include "../Encoded/ForwardDecoder.hpp"
#include "../Encoded/ReverseDecoder.hpp"
#include "StringTypeTraits.hpp"

namespace Ystring { namespace Generic
{
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

    template <typename Str, typename It, typename Enc1, typename Enc2>
    void append(StringReference<Str> dst, Range<It> src,
                Enc1 dstEncoding, Enc2 srcEncoding)
    {
        Detail::appendImpl(
                dst, src, dstEncoding, srcEncoding,
                CanCopyRawValues<
                        typename StringReference<Str>::ValueType,
                        Enc1,
                        typename Range<It>::ValueType, Enc2>());
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
        return caseInsensitiveEqual(
                Encoded::makeForwardDecoder(str, encoding),
                Encoded::makeForwardDecoder(cmp, encoding));
    }

    template <typename It1, typename It2, typename Enc>
    bool caseInsensitiveLess(Range<It1> str,
                             Range<It2> cmp,
                             Enc encoding)
    {
        return caseInsensitiveLess(
                Encoded::makeForwardDecoder(str, encoding),
                Encoded::makeForwardDecoder(cmp, encoding));
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

    template <typename It, typename Enc>
    uint32_t getCodePoint(Range<It> str, ptrdiff_t pos, Enc encoding)
    {
        auto it = str.begin();
        if (pos > 0)
        {
            encoding.skipNext(it, str.end(), static_cast<size_t>(pos));
        }
        else if (pos < 0)
        {
            it = str.end();
            encoding.skipPrev(str.begin(), it, static_cast<size_t>(-pos));
        }
        uint32_t chr;
        if (!encoding.next(chr, it, str.end()))
            YSTRING_THROW("No character at position " + std::to_string(pos));
        return chr;
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

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> split(Range<It1> str,
                           Range<It2> cmp,
                           Enc encoding,
                           ptrdiff_t maxSplits,
                           SplitFlags_t flags)
    {
        if (SplitFlags::isCaseInsensitive(flags) || maxSplits < 0)
            return Detail::splitImpl<Str>(
                    str, cmp, encoding, maxSplits, flags, std::false_type());
        else
            return Detail::splitImpl<Str>(
                    str, cmp, encoding, maxSplits, flags,
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

    template <typename It, typename Enc, typename UnaryPred>
    Range<It> trim(Range<It> str,
                   Enc encoding,
                   UnaryPred trimChar)
    {
        return trimEnd(trimStart(str, encoding, trimChar),
                       encoding, trimChar);
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
            return Encoded::startsWith(
                    Encoded::makeReverseDecoder(str, encoding),
                    Encoded::makeReverseDecoder(cmp, encoding),
                    flags);
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
                result.push_back(Str(token.begin(), token.end()));
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
                result.push_back(Str(token.begin(), token.end()));
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
                result.push_back(Str(str.begin(), str.end()));
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
                result.push_back(Str(token.begin(), token.end()));
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
                result.push_back(Str(token.begin(), token.end()));
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
                result.push_back(Str(str.begin(), str.end()));
            }
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
    }
}}
