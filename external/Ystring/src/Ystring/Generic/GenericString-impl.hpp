//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "DecoderStringFunctions.hpp"
#include "Encoder.hpp"
#include "ForwardDecoder.hpp"
#include "ReverseDecoder.hpp"
#include "GenericConvert.hpp"
#include "GenericJoin.hpp"
#include "GenericSplit.hpp"
#include "StringTypeTraits.hpp"

namespace Ystring { namespace Generic
{
    namespace Detail
    {
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


    template <typename It1, typename It2, typename Enc>
    int32_t caseInsensitiveCompare(Range<It1> str,
                                   Range<It2> cmp,
                                   Enc encoding)
    {
        return caseInsensitiveCompare(
                EncodedString::makeForwardDecoder(str, encoding),
                EncodedString::makeForwardDecoder(cmp, encoding));
    }

    template <typename It1, typename It2, typename Enc>
    bool caseInsensitiveEqual(Range<It1> str,
                              Range<It2> cmp,
                              Enc encoding)
    {
        return caseInsensitiveEqual(
                EncodedString::makeForwardDecoder(str, encoding),
                EncodedString::makeForwardDecoder(cmp, encoding));
    }

    template <typename It1, typename It2, typename Enc>
    bool caseInsensitiveLess(Range<It1> str,
                             Range<It2> cmp,
                             Enc encoding)
    {
        return caseInsensitiveLess(
                EncodedString::makeForwardDecoder(str, encoding),
                EncodedString::makeForwardDecoder(cmp, encoding));
    }

    template <typename It, typename Enc>
    size_t countCharacters(Range<It> str, Enc encoding)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
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
    char32_t getCodePoint(Range<It> str, ptrdiff_t pos, Enc encoding)
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
        char32_t chr;
        if (!encoding.next(chr, it, str.end()))
            YSTRING_THROW("No character at position " + std::to_string(pos));
        return chr;
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
        auto dec = EncodedString::makeReverseDecoder(str, encoding);
        advanceWhile(dec, trimChar);
        return dec.getRange();
    }

    template <typename It, typename Enc, typename UnaryPred>
    Range<It> trimStart(Range<It> str,
                        Enc encoding,
                        UnaryPred trimChar)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        advanceWhile(dec, trimChar);
        return dec.getRange();
    }

    namespace Detail
    {
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
            return EncodedString::startsWith(
                    EncodedString::makeReverseDecoder(str, encoding),
                    EncodedString::makeReverseDecoder(cmp, encoding),
                    flags);
        }
    }
}}
