//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoding.hpp"
#include "DecodeUtf8.hpp"
#include "EncodeUtf8.hpp"

namespace Ystring { namespace Utf8
{
    class Utf8Encoding
    {
    public:
        static const Encoding_t encoding = Encoding::UTF_8;
        typedef char CanonicalType;

        template <typename FwdIt>
        bool next(uint32_t& codePoint, FwdIt& it, FwdIt last)
        {
            switch (nextUtf8CodePoint(codePoint, it, last))
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
            return skipNextUtf8CodePoint(it, last, count);
        }

        template <typename BiIt>
        bool prev(uint32_t& codePoint, BiIt first, BiIt& it)
        {
            switch (prevUtf8CodePoint(codePoint, first, it))
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
            return skipPrevUtf8CodePoint(first, it, count);
        }

        template <typename OutIt>
        OutIt encode(OutIt dst, uint32_t codePoint)
        {
            return addUtf8(dst, codePoint);
        }

        template <typename OutIt>
        OutIt encodeAsBytes(OutIt dst, uint32_t codePoint)
        {
            return addUtf8(dst, codePoint);
        }
    };
}}
