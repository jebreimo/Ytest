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

namespace Ystring { namespace Utf32
{
    template <bool SwapBytes, typename OutIt>
    OutIt addUtf32(OutIt out, uint32_t codePoint);

    template <typename OutIt>
    OutIt addUtf32(OutIt out, uint32_t codePoint);

    template <typename OutIt>
    OutIt addUtf32LE(OutIt out, uint32_t codePoint);

    template <typename OutIt>
    OutIt addUtf32BE(OutIt out, uint32_t codePoint);

    template<bool SwapBytes, typename OutIt>
    OutIt addUtf32AsBytes(OutIt out, uint32_t codePoint);

    template <typename FwdIt>
    size_t encodeUtf32(FwdIt& begin, FwdIt end, uint32_t codePoint);

    template <typename FwdIt>
    size_t encodeUtf32LE(FwdIt& begin, FwdIt end, uint32_t codePoint);

    template <typename FwdIt>
    size_t encodeUtf32BE(FwdIt& begin, FwdIt end, uint32_t codePoint);
}}

#include "EncodeUtf32-impl.hpp"
