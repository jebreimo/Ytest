//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-11
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Ystring/Encoding.hpp"
#include "Ystring/Encodings/DecodeUtf32.hpp"
#include "Ystring/Encodings/EncodeUtf32.hpp"

namespace Ystring { namespace Utf32
{
    template <bool SwapBytes>
    class Utf32EncodingImpl
    {
    public:
        static const auto encoding = SwapBytes ? Encoding::UTF_32_BE
                                               : Encoding::UTF_32_LE;
        typedef char32_t CanonicalType;

        template<typename FwdIt>
        bool next(FwdIt& it, FwdIt last)
        {
            char32_t codePoint;
            return Encodings::nextUtf32CodePoint<SwapBytes>(codePoint, it, last)
                   == DecoderResult::OK;
        }

        template <typename FwdIt>
        bool next(char32_t& codePoint, FwdIt& it, FwdIt last)
        {
            switch (Encodings::nextUtf32CodePoint<SwapBytes>(codePoint, it, last))
            {
                case DecoderResult::END_OF_STRING:
                    return false;
                case DecoderResult::INCOMPLETE:
                    YSTRING_THROW("Incomplete character.");
                case DecoderResult::INVALID:
                    YSTRING_THROW("Invalid character.");
                default:
                    break;
            }
            return true;
        }

        template <typename BiIt>
        bool prev(char32_t& codePoint, BiIt first, BiIt& it)
        {
            switch (Encodings::prevUtf32CodePoint<SwapBytes>(codePoint, first, it))
            {
                case DecoderResult::END_OF_STRING:
                    return false;
                case DecoderResult::INCOMPLETE:
                    YSTRING_THROW("Incomplete character.");
                case DecoderResult::INVALID:
                    YSTRING_THROW("Invalid character.");
                default:
                    break;
            }
            return true;
        }

        template <typename FwdIt>
        bool skipNext(FwdIt& it, FwdIt last, size_t count)
        {
            return Encodings::skipNextUtf32CodePoint<FwdIt>(it, last, count);
        }

        template <typename BiIt>
        bool skipPrev(BiIt first, BiIt& it, size_t count)
        {
            return Encodings::skipPrevUtf32CodePoint<BiIt>(first, it, count);
        }

        template <typename OutIt>
        OutIt encode(OutIt dst, char32_t codePoint)
        {
            return Encodings::addUtf32<SwapBytes>(dst, codePoint);
        }

        template <typename OutIt>
        OutIt encodeAsBytes(OutIt dst, char32_t codePoint)
        {
            return Encodings::addUtf32AsBytes<SwapBytes>(dst, codePoint);
        }
    };

    typedef Utf32EncodingImpl<false> Utf32Encoding;
    typedef Utf32EncodingImpl<IsBigEndian> Utf32LEEncoding;
    typedef Utf32EncodingImpl<IsLittleEndian> Utf32BEEncoding;
}}
