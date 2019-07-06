//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Ystring/Encoding.hpp"
#include "Ystring/Encodings/DecodeUtf16.hpp"
#include "Ystring/Encodings/EncodeUtf16.hpp"

namespace Ystring { namespace Utf16
{
    template <bool SwapBytes>
    class Utf16EncodingImpl
    {
    public:
        static const auto encoding = SwapBytes ? Encoding::UTF_16_BE
                                               : Encoding::UTF_16_LE;
        typedef wchar_t CanonicalType;

        template<typename FwdIt>
        bool next(FwdIt& it, FwdIt last)
        {
            char32_t codePoint;
            return Encodings::nextUtf16CodePoint<SwapBytes>(codePoint, it, last)
                   == DecoderResult::OK;
        }

        template <typename FwdIt>
        bool next(char32_t& codePoint, FwdIt& it, FwdIt last)
        {
            switch (Encodings::nextUtf16CodePoint<SwapBytes>(codePoint, it, last))
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
            switch (Encodings::prevUtf16CodePoint<SwapBytes>(codePoint, first, it))
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
            return Encodings::skipNextUtf16CodePoint<SwapBytes>(it, last, count);
        }

        template <typename BiIt>
        bool skipPrev(BiIt first, BiIt& it, size_t count)
        {
            return Encodings::skipPrevUtf16CodePoint<SwapBytes>(first, it, count);
        }

        template <typename OutIt>
        OutIt encode(OutIt dst, char32_t codePoint)
        {
            return Encodings::addUtf16(dst, codePoint);
        }

        template <typename OutIt>
        OutIt encodeAsBytes(OutIt dst, char32_t codePoint)
        {
            return Encodings::addUtf16AsBytes<SwapBytes>(dst, codePoint);
        }
    };

    typedef Utf16EncodingImpl<false> Utf16Encoding;
    typedef Utf16EncodingImpl<IsBigEndian> Utf16LEEncoding;
    typedef Utf16EncodingImpl<IsLittleEndian> Utf16BEEncoding;
}}
