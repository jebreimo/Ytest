//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <type_traits>
#include "../Utilities/Union16.hpp"
#include "../DecoderResult.hpp"

namespace Ystring { namespace Utf16 {

#ifdef YSTRING_WCHAR_IS_2_BYTES
	typedef uint16_t UnsignedWChar;
#else
	typedef uint32_t UnsignedWChar;
#endif

namespace Detail
{
    using Utilities::swapEndianness;

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint8_t)
    {
        if (it == end)
            return DecoderResult::END_OF_STRING;

        FwdIt initialIt = it;
        Utilities::Union16 chr;
        chr.u8[SwapBytes ? 1 : 0] = *it++;

        if (it == end)
        {
            it = initialIt;
            return DecoderResult::INCOMPLETE;
        }

        chr.u8[SwapBytes ? 0 : 1] = *it++;

        word = chr.u16;
        return DecoderResult::OK;
    }

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint16_t)
    {
        if (it == end)
            return DecoderResult::END_OF_STRING;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecoderResult::OK;
    }

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint32_t)
    {
        if (it == end)
            return DecoderResult::END_OF_STRING;
        else if (*it > 0xFFFFu)
            return DecoderResult::INVALID;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecoderResult::OK;
    }

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextWord(uint16_t& word, FwdIt& it, FwdIt end, char)
    {
        return nextWord<SwapBytes>(word, it, end, uint8_t());
    }

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextWord(uint16_t& word, FwdIt& it, FwdIt end, wchar_t)
    {
        return nextWord<SwapBytes>(word, it, end, UnsignedWChar());
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t prevWord(uint16_t& word, BiIt begin, BiIt& it, uint8_t)
    {
        if (it == begin)
            return DecoderResult::END_OF_STRING;

        BiIt initialIt = it;
        Utilities::Union16 chr;
        chr.u8[SwapBytes ? 0 : 1] = uint8_t(*(--it));

        if (it == begin)
        {
            it = initialIt;
            return DecoderResult::INCOMPLETE;
        }

        chr.u8[SwapBytes ? 1 : 0] = uint8_t(*(--it));

        word = chr.u16;
        return DecoderResult::OK;
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t prevWord(uint16_t& word, BiIt begin, BiIt& it, uint16_t)
    {
        if (it == begin)
            return DecoderResult::END_OF_STRING;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecoderResult::OK;
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t prevWord(uint16_t& word, BiIt begin, BiIt& it, uint32_t)
    {
        if (it == begin)
            return DecoderResult::END_OF_STRING;
        else if (*it > 0xFFFFu)
            return DecoderResult::INVALID;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecoderResult::OK;
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t prevWord(uint16_t& word, BiIt begin, BiIt& it, char)
    {
        return prevWord<SwapBytes>(word, begin, it, uint8_t());
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t prevWord(uint16_t& word, BiIt begin, BiIt& it, wchar_t)
    {
        return prevWord<SwapBytes>(word, begin, it, UnsignedWChar());
    }

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t skipNextWord(uint16_t& word, FwdIt& it, FwdIt end)
    {
        typedef typename std::iterator_traits<FwdIt>::value_type ValueType;
        auto res = nextWord<SwapBytes>(word, it, end, ValueType());
        if (res != DecoderResult::OK && res != DecoderResult::END_OF_STRING)
            ++it;
        return res;
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t skipPrevWord(uint16_t& word, BiIt begin, BiIt& it)
    {
        typedef typename std::iterator_traits<BiIt>::value_type ValueType;
        auto res = prevWord<SwapBytes>(word, begin, it, ValueType());
        if (res != DecoderResult::OK && res != DecoderResult::END_OF_STRING)
            --it;
        return res;
    }
}

template <bool SwapBytes, typename FwdIt>
DecoderResult_t nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    uint16_t chr;
    typedef typename std::iterator_traits<FwdIt>::value_type ValueType;
    auto res = Detail::nextWord<SwapBytes>(chr, it, end, ValueType());
    if (res != DecoderResult::OK)
        return res;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecoderResult::OK;
    }
    else if (0xDC00 <= chr)
    {
        codePoint = chr;
        return DecoderResult::INVALID;
    }

    codePoint = uint32_t(chr & 0x3FF) << 10;

    res = Detail::nextWord<SwapBytes>(chr, it, end, ValueType());
    if (res == DecoderResult::END_OF_STRING)
        return DecoderResult::INCOMPLETE;
    else if (res != DecoderResult::OK)
        return res;

    if (chr < 0xDC00 || 0xE000 <= chr)
    {
        codePoint |= chr;
        return DecoderResult::INVALID;
    }

    codePoint |= chr & 0x3FF;
    codePoint += 0x10000;

    return DecoderResult::OK;
}

template <bool SwapBytes, typename BiIt>
DecoderResult_t prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    uint16_t chr;
    typedef typename std::iterator_traits<BiIt>::value_type ValueType;
    auto res = Detail::prevWord<SwapBytes>(chr, begin, it,
                                                  ValueType());
    if (res != DecoderResult::OK)
        return res;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecoderResult::OK;
    }
    else if (chr < 0xDC00)
    {
        codePoint = chr;
        return DecoderResult::INVALID;
    }

    codePoint = uint32_t(chr) & 0x3FF;

    res = Detail::prevWord<SwapBytes>(chr, begin, it, ValueType());
    if (res == DecoderResult::END_OF_STRING)
        return DecoderResult::INCOMPLETE;
    else if (res != DecoderResult::OK)
        return res;

    if (chr < 0xD800 || 0xDC00 <= chr)
    {
        codePoint |= chr << 10;
        return DecoderResult::INVALID;
    }

    codePoint |= (chr & 0x3FF) << 10;
    codePoint += 0x10000;

    return DecoderResult::OK;
}

template <bool SwapBytes, typename FwdIt>
bool skipNextUtf16CodePoint(FwdIt& it, FwdIt end)
{
    uint16_t chr;
    auto res = Detail::skipNextWord<SwapBytes>(chr, it, end);
    if (res != DecoderResult::OK)
        return res != DecoderResult::END_OF_STRING;
    if (0xD800 <= chr && chr < 0xDC00)
        Detail::skipNextWord<SwapBytes>(chr, it, end);
    return true;
}

template <bool SwapBytes, typename BiIt>
bool skipPrevUtf16CodePoint(BiIt begin, BiIt& it)
{
    uint16_t chr;
    auto res = Detail::skipPrevWord<SwapBytes>(chr, begin, it);
    if (res != DecoderResult::OK)
        return res != DecoderResult::END_OF_STRING;
    if (0xD800 <= chr && chr < 0xDC00)
        Detail::skipPrevWord<SwapBytes>(chr, begin, it);
    return true;
}

}}
