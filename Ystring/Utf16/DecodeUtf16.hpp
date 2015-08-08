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

namespace Ystring { namespace Utf16 {

using Utilities::IsBigEndian;
using Utilities::IsLittleEndian;

template <typename FwdIt, bool SwapBytes = false>
DecoderResult_t nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename FwdIt>
DecoderResult_t nextUtf16LECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, IsBigEndian>(codePoint, it, end);
}

template <typename FwdIt>
DecoderResult_t nextUtf16BECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, IsLittleEndian>(codePoint, it, end);
}

template <typename BiIt, bool SwapBytes = false>
DecoderResult_t prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename BiIt>
DecoderResult_t prevUtf16LECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, IsBigEndian>(codePoint, begin, it);
}

template <typename BiIt>
DecoderResult_t prevUtf16BECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, IsLittleEndian>(codePoint, begin, it);
}

template <typename FwdIt, bool SwapBytes = false>
bool skipNextUtf16CodePoint(FwdIt& it, FwdIt end);

template <typename FwdIt>
bool skipNextUtf16LECodePoint(FwdIt& it, FwdIt end)
{
    return skipNextUtf16CodePoint<FwdIt, IsBigEndian>(it, end);
}

template <typename FwdIt>
bool skipNextUtf16BECodePoint(FwdIt& it, FwdIt end)
{
    return skipNextUtf16CodePoint<FwdIt, IsLittleEndian>(it, end);
}

template <typename BiIt, bool SwapBytes = false>
bool skipPrevUtf16CodePoint(BiIt begin, BiIt& it);

template <typename BiIt>
bool skipPrevUtf16LECodePoint(BiIt begin, BiIt& it)
{
    return skipPrevUtf16CodePoint<BiIt, IsBigEndian>(begin, it);
}

template <typename BiIt>
bool skipPrevUtf16BECodePoint(BiIt begin, BiIt& it)
{
    return skipPrevUtf16CodePoint<BiIt, IsLittleEndian>(begin, it);
}

}}

#include "DecodeUtf16-impl.hpp"
