//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-11
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <type_traits>
#include "../Utilities/Union32.hpp"
#include "../DecoderResult.hpp"

namespace Ystring { namespace Utf32 {

typedef std::make_unsigned<wchar_t>::type UnsignedWChar;

namespace Details
{
    using Utilities::swapEndianness;

    template <typename FwdIt, bool SwapBytes>
    DecoderResult_t nextWord(uint32_t& word, FwdIt& it, FwdIt end, uint8_t)
    {
        if (it == end)
            return DecoderResult::END_OF_STRING;

        FwdIt initialIt = it;
        Utilities::Union32 chr;
        chr.u8[SwapBytes ? 3 : 0] = uint8_t(*it++);
        for (auto i = 1; i < 4; ++i)
        {
            if (it == end)
            {
                it = initialIt;
                return DecoderResult::INCOMPLETE;
            }
            chr.u8[SwapBytes ? 3 - i : i] = uint8_t(*it++);
        }

        word = chr.u32;
        return DecoderResult::OK;
    }

    template <typename FwdIt, bool SwapBytes>
    DecoderResult_t nextWord(uint32_t& word, FwdIt& it, FwdIt end, uint32_t)
    {
        if (it == end)
            return DecoderResult::END_OF_STRING;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecoderResult::OK;
    }

    template <typename FwdIt, bool SwapBytes>
    DecoderResult_t nextWord(uint32_t& word, FwdIt& it, FwdIt end, char)
    {
        return nextWord<FwdIt, SwapBytes>(word, it, end, uint8_t());
    }

    template <typename FwdIt, bool SwapBytes>
    DecoderResult_t nextWord(uint32_t& word, FwdIt& it, FwdIt end, wchar_t)
    {
        return nextWord<FwdIt, SwapBytes>(word, it, end, uint32_t());
    }

    template <typename BiIt, bool SwapBytes>
    DecoderResult_t prevWord(uint32_t& word, BiIt begin, BiIt& it, uint8_t)
    {
        if (it == begin)
            return DecoderResult::END_OF_STRING;

        BiIt initialIt = it;
        Utilities::Union32 chr;
        chr.u8[SwapBytes ? 3 : 0] = uint8_t(*(--it));
        for (auto i = 1; i < 4; ++i)
        {
            if (it == begin)
            {
                it = initialIt;
                return DecoderResult::INCOMPLETE;
            }
            chr.u8[SwapBytes ? 3 - i : i] = uint8_t(*(--it));
        }

        word = chr.u32;
        return DecoderResult::OK;
    }

    template <typename BiIt, bool SwapBytes>
    DecoderResult_t prevWord(uint32_t& word, BiIt begin, BiIt& it, uint32_t)
    {
        if (it == begin)
            return DecoderResult::END_OF_STRING;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecoderResult::OK;
    }

    template <typename BiIt, bool SwapBytes>
    DecoderResult_t prevWord(uint32_t& word, BiIt begin, BiIt& it, char)
    {
        return prevWord<BiIt, SwapBytes>(word, begin, it, uint8_t());
    }

    template <typename BiIt, bool SwapBytes>
    DecoderResult_t prevWord(uint32_t& word, BiIt begin, BiIt& it, wchar_t)
    {
        return prevWord<BiIt, SwapBytes>(word, begin, it, UnsignedWChar());
    }

    template <typename FwdIt, typename T>
    bool skipNextWord(FwdIt& it, FwdIt end, T)
    {
        if (it == end)
            return false;
        ++it;
        return true;
    }

    template <typename FwdIt>
    bool skipNextWord(FwdIt& it, FwdIt end, uint8_t)
    {
        if (it == end)
            return false;

        for (auto i = 0; i < 4; ++i)
        {
            if (++it == end)
                break;
        }
        return true;
    }

    template <typename FwdIt>
    bool skipNextWord(FwdIt& it, FwdIt end, char)
    {
        return skipNextWord<FwdIt>(it, end, uint8_t());
    }

    template <typename BiIt, typename T>
    bool skipPrevWord(BiIt begin, BiIt& it, T)
    {
        if (it == begin)
            return false;
        --it;
        return true;
    }

    template <typename BiIt>
    bool skipPrevWord(BiIt begin, BiIt& it)
    {
        if (it == begin)
            return false;

        for (auto i = 0; i < 4; ++i)
        {
            if (--it == begin)
                break;
        }
        return true;
    }

    template <typename BiIt>
    bool skipPrevWord(BiIt begin, BiIt& it, char)
    {
        return skipPrevWord<BiIt>(begin, it, uint8_t());
    }
}

template <typename FwdIt, bool SwapBytes>
DecoderResult_t nextUtf32CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    typedef typename std::iterator_traits<FwdIt>::value_type ValueType;
    return Details::nextWord<FwdIt, SwapBytes>(codePoint, it, end,
                                               ValueType());
}

template <typename BiIt, bool SwapBytes>
DecoderResult_t prevUtf32CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    typedef typename std::iterator_traits<BiIt>::value_type ValueType;
    return Details::prevWord<BiIt, SwapBytes>(codePoint, begin, it,
                                              ValueType());
}

template <typename FwdIt>
bool skipNextUtf32CodePoint(FwdIt& it, FwdIt end)
{
    typedef typename std::iterator_traits<FwdIt>::value_type ValueType;
    return Details::skipNextWord(it, end, ValueType());
}

template <typename BiIt>
bool skipPrevUtf32CodePoint(BiIt begin, BiIt& it)
{
    typedef typename std::iterator_traits<BiIt>::value_type ValueType;
    return Details::skipPrevWord(begin, it, ValueType());
}

}}
