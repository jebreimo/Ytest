//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoding.hpp"
#include "../Encodings/DecodeUtf8.hpp"
#include "../Encodings/EncodeUtf8.hpp"

namespace Ystring { namespace Utf8
{
    class Utf8Encoding
    {
    public:
        static const Encoding_t encoding = Encoding::UTF_8;
        typedef char CanonicalType;

        template <typename FwdIt>
        bool next(FwdIt& it, FwdIt last)
        {
            char32_t codePoint;
            return Encodings::nextUtf8CodePoint(codePoint, it, last) ==
                    DecoderResult::OK;
        }

        template <typename FwdIt>
        bool next(char32_t& codePoint, FwdIt& it, FwdIt last)
        {
            switch (Encodings::nextUtf8CodePoint(codePoint, it, last))
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
            return Encodings::skipNextUtf8CodePoint(it, last, count);
        }

        template <typename BiIt>
        bool prev(char32_t& codePoint, BiIt first, BiIt& it)
        {
            switch (Encodings::prevUtf8CodePoint(codePoint, first, it))
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
        bool skipPrev(BiIt first, BiIt& it, size_t count)
        {
            return Encodings::skipPrevUtf8CodePoint(first, it, count);
        }

        template <typename OutIt>
        OutIt encode(OutIt dst, char32_t codePoint)
        {
            return Encodings::addUtf8(dst, codePoint);
        }

        template <typename OutIt>
        OutIt encodeAsBytes(OutIt dst, char32_t codePoint)
        {
            return Encodings::addUtf8(dst, codePoint);
        }
    };
}}
