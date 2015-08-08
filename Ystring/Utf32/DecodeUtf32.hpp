//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-11
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

namespace Ystring { namespace Utf32 {

using Utilities::IsBigEndian;
using Utilities::IsLittleEndian;

template <typename FwdIt, bool SwapBytes = false>
DecoderResult_t nextUtf32CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename FwdIt>
DecoderResult_t nextUtf32LECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf32CodePoint<FwdIt, IsBigEndian>(codePoint, it, end);
}

template <typename FwdIt>
DecoderResult_t nextUtf32BECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf32CodePoint<FwdIt, IsLittleEndian>(codePoint, it, end);
}

template <typename BiIt, bool SwapBytes = false>
DecoderResult_t prevUtf32CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename BiIt>
DecoderResult_t prevUtf32LECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf32CodePoint<BiIt, IsBigEndian>(codePoint, begin, it);
}

template <typename BiIt>
DecoderResult_t prevUtf32BECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf32CodePoint<BiIt, IsLittleEndian>(codePoint, begin, it);
}

template <typename FwdIt, bool SwapBytes = false>
bool skipNextUtf32CodePoint(FwdIt& it, FwdIt end);

template <typename FwdIt>
bool skipNextUtf32LECodePoint(FwdIt& it, FwdIt end)
{
    return skipNextUtf32CodePoint<FwdIt, IsBigEndian>(it, end);
}

template <typename FwdIt>
bool skipNextUtf32BECodePoint(FwdIt& it, FwdIt end)
{
    return skipNextUtf32CodePoint<FwdIt, IsLittleEndian>(it, end);
}

template <typename BiIt, bool SwapBytes = false>
bool skipPrevUtf32CodePoint(BiIt begin, BiIt& it);

template <typename BiIt>
bool skipPrevUtf32LECodePoint(BiIt begin, BiIt& it)
{
    return skipPrevUtf32CodePoint<BiIt, IsBigEndian>(begin, it);
}

template <typename BiIt>
bool skipPrevUtf32BECodePoint(BiIt begin, BiIt& it)
{
    return skipPrevUtf32CodePoint<BiIt, IsLittleEndian>(begin, it);
}

}}

#include "DecodeUtf32-impl.hpp"
