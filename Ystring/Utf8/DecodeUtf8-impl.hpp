//****************************************************************************
// Copyright © 2011, Jan Erik Breimo.
// Created 2011-07-14 by Jan Erik Breimo
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <algorithm>
#include <cassert>

namespace Ystring { namespace Utf8
{
    namespace Detail
    {
        static inline bool isContinuation(uint8_t c)
        {
            return (c & 0xC0) == 0x80;
        }

        static inline bool isAscii(uint32_t c)
        {
            return  (c & 0x80) == 0;
        }
    }

    template <typename FwdIt>
    bool isValidUtf8(FwdIt begin, FwdIt end, bool acceptIncompleteAtEnd)
    {
        unsigned cp;
        unsigned result;
        while ((result = nextUtf8CodePoint(cp, begin, end)) == 0)
        {
        }
        return (result == DecoderResult::END_OF_STRING) ||
               (acceptIncompleteAtEnd &&
                       (result & DecoderResult::END_OF_STRING));
    }

    template <typename FwdIt>
    DecoderResult_t nextUtf8CodePoint(uint32_t& codePoint,
                                      FwdIt& it, FwdIt end)
    {
        if (it == end)
            return DecoderResult::END_OF_STRING;

        if (Detail::isAscii(*it))
        {
            codePoint = (uint8_t)*it++;
            return DecoderResult::OK;
        }

        if (Detail::isContinuation(*it) || uint8_t(*it) >= 0xFE)
            return DecoderResult::INVALID;

        size_t count = 1;
        unsigned bit = 0x20;
        codePoint = *it & 0x3F;
        while (codePoint & bit)
        {
            bit >>= 1;
            ++count;
        }

        codePoint &= bit - 1;

        FwdIt initialIt = it;
        while (++it != end && count && Detail::isContinuation(*it))
        {
            codePoint <<= 6;
            codePoint |= *it & 0x3F;
            --count;
        }

        if (count)
        {
            it = initialIt;
            return DecoderResult::INCOMPLETE;
        }

        return DecoderResult::OK;
    }

    template <typename BiIt>
    DecoderResult_t prevUtf8CodePoint(uint32_t& codePoint,
                                      BiIt begin, BiIt& it)
    {
        if (it == begin)
            return DecoderResult::END_OF_STRING;

        BiIt initialIt = it;
        --it;
        if (Detail::isAscii(*it))
        {
            codePoint = (uint8_t)*it;
            return DecoderResult::OK;
        }

        codePoint = 0;
        uint8_t mask = 0xC0;
        uint8_t bit = 0x20;
        uint32_t shift = 0;
        while (Detail::isContinuation(*it))
        {
            if (bit == 1 || it == begin)
            {
                it = initialIt;
                return DecoderResult::INVALID;
            }
            mask |= bit;
            bit >>= 1;
            codePoint |= uint32_t(*it & 0x3F) << shift;
            shift += 6;
            --it;
        }

        uint8_t byte = *it;
        if ((byte & mask) != uint8_t(mask << 1))
        {
            it = initialIt;
            if ((byte & mask) != mask)
                return DecoderResult::INVALID;
            else
                return DecoderResult::INCOMPLETE;
        }

        codePoint |= (byte & ~mask) << shift;

        return DecoderResult::OK;
    }

    template <typename FwdIt>
    bool skipNextUtf8CodePoint(FwdIt& it, FwdIt end, size_t count)
    {
        if (it == end && count != 0)
            return false;

        for (auto i = 0u; i < count; ++i)
        {
            do
            {
                ++it;
            }
            while (it != end && Detail::isContinuation(*it));
        }

        return true;
    }

    template <typename BiIt>
    bool skipPrevUtf8CodePoint(BiIt begin, BiIt& it, size_t count)
    {
        if (it == begin)
            return false;

        for (auto i = 0u; i < count; ++i)
        {
            do
            {
                --it;
            }
            while (it != begin && Detail::isContinuation(*it));
        }

        return true;
    }
}}
