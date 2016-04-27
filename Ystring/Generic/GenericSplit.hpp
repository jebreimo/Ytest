//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <vector>
#include "../SplitFlags.hpp"
#include "DecoderStringFunctions.hpp"
#include "ForwardDecoder.hpp"
#include "ReverseDecoder.hpp"
#include "RangeAlgorithms.hpp"
#include "StringTypeTraits.hpp"

namespace Ystring { namespace Generic {
    namespace Detail {
        template<typename Str, typename Decoder, typename NextTokenFunc>
        std::vector<Str> splitImpl(
                Decoder str,
                NextTokenFunc nextTokenFunc,
                size_t maxSplits,
                SplitFlags_t flags);

        template<typename Str, typename It1, typename It2, typename Enc>
        std::vector<Str> splitImpl(
                Range<It1> str,
                Range<It2> cmp,
                Enc encoding,
                ptrdiff_t maxSplits,
                SplitFlags_t flags,
                std::true_type);

        template<typename Str, typename It1, typename It2, typename Enc>
        std::vector<Str> splitImpl(
                Range<It1> str,
                Range<It2> cmp,
                Enc encoding,
                ptrdiff_t maxSplits,
                SplitFlags_t flags,
                std::false_type);
    }

    template<typename Str, typename It, typename Enc, typename Predicate>
    std::vector<Str> splitIf(Range<It> str,
                             Enc encoding,
                             Predicate predicate,
                             ptrdiff_t maxSplits,
                             SplitFlags_t flags)
    {
        if (maxSplits >= 0)
            return Detail::splitImpl<Str>(
                    EncodedString::makeForwardDecoder(str, encoding),
                    [&](EncodedString::ForwardDecoder<It, Enc>& d)
                    {
                        return nextToken(d, predicate);
                    },
                    maxSplits, flags);
        else
            return Detail::splitImpl<Str>(
                    EncodedString::makeReverseDecoder(str, encoding),
                    [&](EncodedString::ReverseDecoder<It, Enc>& d)
                    {
                        return nextToken(d, predicate);
                    },
                    -maxSplits, flags);
    }

    template<typename Str, typename It, typename Enc>
    std::vector<Str> split(Range<It> str,
                           Enc encoding,
                           ptrdiff_t maxSplits,
                           SplitFlags_t flags)
    {
        return splitIf<Str>(str, encoding, Unicode::isWhitespace,
                            maxSplits, flags);
    }

    template<typename Str, typename It1, typename It2, typename Enc>
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

    template<typename Str, typename It, typename Enc>
    std::vector<Str> splitLines(Range<It> str,
                                Enc encoding,
                                ptrdiff_t maxSplits,
                                SplitFlags_t flags)
    {
        if (maxSplits >= 0)
            return Detail::splitImpl<Str>(
                    EncodedString::makeForwardDecoder(str, encoding),
                    [&](EncodedString::ForwardDecoder<It, Enc>& d)
                    {
                        return nextLine(d);
                    },
                    maxSplits, flags);
        else
            return Detail::splitImpl<Str>(
                    EncodedString::makeReverseDecoder(str, encoding),
                    [&](EncodedString::ReverseDecoder<It, Enc>& d)
                    {
                        return nextLine(d);
                    },
                    -maxSplits, flags);
    }

    namespace Detail {

        template<typename Decoder, typename NextTokenFunc>
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

        template<typename Str, typename Decoder, typename NextTokenFunc>
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

        template<typename It1, typename It2>
        Range<It1> nextToken(Range<It1>& str, Range<It2> cmp)
        {
            auto sep = search(str, cmp);
            auto token = !empty(sep) ? makeRange(str.begin(), sep.begin())
                                     : str;
            str.begin() = sep.end();
            return token;
        }

        template<typename It1, typename It2>
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

        template<typename Str, typename It1, typename It2, typename Enc>
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

        template<typename Str, typename It1, typename It2, typename Enc>
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
                auto cmpDec = EncodedString::makeForwardDecoder(cmp, encoding);
                return splitImpl<Str>(
                        EncodedString::makeForwardDecoder(str, encoding),
                        [=](EncodedString::ForwardDecoder<It1, Enc>& d)
                        {
                            return nextToken(d, cmpDec, findFlags);
                        },
                        size_t(maxSplits), flags);
            }
            else
            {
                auto cmpDec = EncodedString::makeReverseDecoder(cmp, encoding);
                return splitImpl<Str>(
                        EncodedString::makeReverseDecoder(str, encoding),
                        [=](EncodedString::ReverseDecoder<It1, Enc>& d)
                        {
                            return nextToken(d, cmpDec, findFlags);
                        },
                        size_t(-maxSplits), flags);
            }
        }
    }
}}
