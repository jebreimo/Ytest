//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <limits>
#include <string>
#include "../DecoderResult.hpp"
#include "../Utilities/Endian.hpp"

namespace Ystring { namespace Utf16
{
    using Utilities::IsBigEndian;
    using Utilities::IsLittleEndian;

    template <bool SwapBytes, typename FwdIt>
    DecoderResult_t nextUtf16CodePoint(uint32_t& codePoint,
                                       FwdIt& it, FwdIt end);

    template <typename FwdIt>
    DecoderResult_t nextUtf16LECodePoint(uint32_t& codePoint,
                                         FwdIt& it, FwdIt end)
    {
        return nextUtf16CodePoint<IsBigEndian>(codePoint, it, end);
    }

    template <typename FwdIt>
    DecoderResult_t nextUtf16BECodePoint(uint32_t& codePoint,
                                         FwdIt& it, FwdIt end)
    {
        return nextUtf16CodePoint<IsLittleEndian>(codePoint, it, end);
    }

    template <bool SwapBytes, typename BiIt>
    DecoderResult_t prevUtf16CodePoint(uint32_t& codePoint,
                                       BiIt begin, BiIt& it);

    template <typename BiIt>
    DecoderResult_t prevUtf16LECodePoint(uint32_t& codePoint,
                                         BiIt begin, BiIt& it)
    {
        return prevUtf16CodePoint<IsBigEndian>(codePoint, begin, it);
    }

    template <typename BiIt>
    DecoderResult_t prevUtf16BECodePoint(uint32_t& codePoint,
                                         BiIt begin, BiIt& it)
    {
        return prevUtf16CodePoint<IsLittleEndian>(codePoint, begin, it);
    }

    template <bool SwapBytes, typename FwdIt>
    bool skipNextUtf16CodePoint(FwdIt& it, FwdIt end, size_t count);

    template <typename FwdIt>
    bool skipNextUtf16LECodePoint(FwdIt& it, FwdIt end, size_t count)
    {
        return skipNextUtf16CodePoint<IsBigEndian>(it, end, count);
    }

    template <typename FwdIt>
    bool skipNextUtf16BECodePoint(FwdIt& it, FwdIt end, size_t count)
    {
        return skipNextUtf16CodePoint<IsLittleEndian>(it, end, count);
    }

    template <bool SwapBytes, typename BiIt>
    bool skipPrevUtf16CodePoint(BiIt begin, BiIt& it, size_t count);

    template <typename BiIt>
    bool skipPrevUtf16LECodePoint(BiIt begin, BiIt& it, size_t count)
    {
        return skipPrevUtf16CodePoint<IsBigEndian>(begin, it, count);
    }

    template <typename BiIt>
    bool skipPrevUtf16BECodePoint(BiIt begin, BiIt& it, size_t count)
    {
        return skipPrevUtf16CodePoint<IsLittleEndian>(begin, it, count);
    }
}}

#include "DecodeUtf16-impl.hpp"
