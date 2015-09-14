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

namespace Ystring { namespace Utf16
{

    namespace Detail
    {
        template<typename T>
        struct Utf16CharType
        {
            typedef T Type;
        };

        #define YSTRING_DEFINE_UTF16_CHAR_TYPE(type, internalType) \
            template <> \
            struct Utf16CharType<type> \
            { \
                typedef internalType Type; \
            }

        YSTRING_DEFINE_UTF16_CHAR_TYPE(char, uint8_t);
        YSTRING_DEFINE_UTF16_CHAR_TYPE(int8_t, uint8_t);
        YSTRING_DEFINE_UTF16_CHAR_TYPE(int16_t, uint16_t);
        YSTRING_DEFINE_UTF16_CHAR_TYPE(char16_t, uint16_t);
        YSTRING_DEFINE_UTF16_CHAR_TYPE(char32_t, uint32_t);
        YSTRING_DEFINE_UTF16_CHAR_TYPE(int32_t, uint32_t);

        #ifdef YSTRING_WCHAR_IS_2_BYTES
            YSTRING_DEFINE_UTF16_CHAR_TYPE(wchar_t, uint16_t);
        #else
            YSTRING_DEFINE_UTF16_CHAR_TYPE(wchar_t, uint32_t);
        #endif

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

        template <bool SwapBytes, typename FwdIt>
        DecoderResult_t skipNextWord(uint16_t& word, FwdIt& it, FwdIt end)
        {
            typedef typename std::iterator_traits<FwdIt>::value_type CharType;
            typedef typename Detail::Utf16CharType<CharType>::Type Utf16Type;
            auto res = nextWord<SwapBytes>(word, it, end, Utf16Type());
            if (res != DecoderResult::OK &&
                res != DecoderResult::END_OF_STRING)
            {
                ++it;
            }
            return res;
        }

        template <bool SwapBytes, typename BiIt>
        DecoderResult_t skipPrevWord(uint16_t& word, BiIt begin, BiIt& it)
        {
            typedef typename std::iterator_traits<BiIt>::value_type CharType;
            typedef typename Detail::Utf16CharType<CharType>::Type Utf16Type;
            auto res = prevWord<SwapBytes>(word, begin, it, Utf16Type());
            if (res != DecoderResult::OK &&
                res != DecoderResult::END_OF_STRING)
            {
                --it;
            }
            return res;
        }
    }

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextUtf16CodePoint(uint32_t& codePoint,
                                       FwdIt& it, FwdIt end)
    {
        uint16_t chr;
        typedef typename std::iterator_traits<FwdIt>::value_type CharType;
        typedef typename Detail::Utf16CharType<CharType>::Type Utf16Type;
        auto res = Detail::nextWord<SwapBytes>(chr, it, end, Utf16Type());
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

        res = Detail::nextWord<SwapBytes>(chr, it, end, Utf16Type());
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
    DecoderResult_t prevUtf16CodePoint(uint32_t& codePoint,
                                       BiIt begin, BiIt& it)
    {
        uint16_t chr;
        typedef typename std::iterator_traits<BiIt>::value_type CharType;
        typedef typename Detail::Utf16CharType<CharType>::Type Utf16Type;
        auto res = Detail::prevWord<SwapBytes>(chr, begin, it, Utf16Type());
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

        res = Detail::prevWord<SwapBytes>(chr, begin, it, Utf16Type());
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
    bool skipNextUtf16CodePoint(FwdIt& it, FwdIt end, size_t count)
    {
        for (auto i = 0u; i < count; ++i)
        {
            uint16_t chr;
            auto res = Detail::skipNextWord<SwapBytes>(chr, it, end);
            if (res != DecoderResult::OK)
                return res != DecoderResult::END_OF_STRING;
            if (0xD800 <= chr && chr < 0xDC00)
                Detail::skipNextWord<SwapBytes>(chr, it, end);
        }
        return true;
    }

    template <bool SwapBytes, typename BiIt>
    bool skipPrevUtf16CodePoint(BiIt begin, BiIt& it, size_t count)
    {
        for (auto i = 0u; i < count; ++i)
        {
            uint16_t chr;
            auto res = Detail::skipPrevWord<SwapBytes>(chr, begin, it);
            if (res != DecoderResult::OK)
                return res != DecoderResult::END_OF_STRING;
            if (0xD800 <= chr && chr < 0xDC00)
                Detail::skipPrevWord<SwapBytes>(chr, begin, it);
        }
        return true;
    }

}}
