//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <algorithm>
#include <cstdint>

namespace Ystring { namespace Utilities {

union Union64
{
    Union64() : u64(0)
    {}

    explicit Union64(uint64_t n) : u64(n)
    {}

    template <typename T>
    explicit Union64(const T (&n)[2])
    {
        u32[0] = static_cast<uint32_t>(n[0]);
        u32[1] = static_cast<uint32_t>(n[1]);
    }

    template <typename T>
    explicit Union64(const T (&n)[4])
    {
        u16[0] = static_cast<uint16_t>(n[0]);
        u16[1] = static_cast<uint16_t>(n[1]);
        u16[2] = static_cast<uint16_t>(n[2]);
        u16[3] = static_cast<uint16_t>(n[3]);
    }

    template <typename T>
    explicit Union64(const T (&n)[8])
    {
        u8[0] = static_cast<uint8_t>(n[0]);
        u8[1] = static_cast<uint8_t>(n[1]);
        u8[2] = static_cast<uint8_t>(n[2]);
        u8[3] = static_cast<uint8_t>(n[3]);
        u8[4] = static_cast<uint8_t>(n[4]);
        u8[5] = static_cast<uint8_t>(n[5]);
        u8[6] = static_cast<uint8_t>(n[6]);
        u8[7] = static_cast<uint8_t>(n[7]);
    }

    template <typename T>
    Union64(T a, T b)
    {
        u32[0] = static_cast<uint32_t>(a);
        u32[1] = static_cast<uint32_t>(b);
    }

    template <typename T>
    Union64(T a, T b, T c, T d)
    {
        u16[0] = static_cast<uint16_t>(a);
        u16[1] = static_cast<uint16_t>(b);
        u16[2] = static_cast<uint16_t>(c);
        u16[3] = static_cast<uint16_t>(d);
    }

    template <typename T>
    Union64(T a, T b, T c, T d, T e, T f, T g, T h)
    {
        u8[0] = static_cast<uint8_t>(a);
        u8[1] = static_cast<uint8_t>(b);
        u8[2] = static_cast<uint8_t>(c);
        u8[3] = static_cast<uint8_t>(d);
        u8[4] = static_cast<uint8_t>(a);
        u8[5] = static_cast<uint8_t>(b);
        u8[6] = static_cast<uint8_t>(c);
        u8[7] = static_cast<uint8_t>(d);
    }

    void reverse()
    {
        std::swap(u8[0], u8[7]);
        std::swap(u8[1], u8[6]);
        std::swap(u8[2], u8[5]);
        std::swap(u8[3], u8[4]);
    }

    int64_t i64;
    uint64_t u64;
    int32_t i32[2];
    uint32_t u32[2];
    int16_t i16[4];
    uint16_t u16[4];
    int8_t i8[8];
    uint8_t u8[8];
};

}}
