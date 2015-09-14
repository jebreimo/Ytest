//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-20
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstdint>

namespace Ystring { namespace Utilities {

inline int countHexDigits(uint32_t c)
{
    auto count = 1;
    while (c >>= 4)
        ++count;
    return count;
}

template <typename FwdIt>
uint32_t fromOct(FwdIt& first, FwdIt last,
                 size_t minLength = 1, size_t maxLength = SIZE_MAX)
{
    uint32_t result = 0;
    for (size_t i = 0; i < maxLength; ++i)
    {
        if (first == last && i < minLength)
            throw std::invalid_argument("Octal sequence is too short.");
        auto tmp = *first;
        if ('0' <= tmp && tmp <= '7')
            result = result * 8 + tmp - '0';
        else if (i < minLength)
            throw std::invalid_argument("Octal sequence is too short.");
        else
            break;
        if (i == sizeof(result) * 8 / 3)
            throw std::invalid_argument("Octal sequence is too long.");
        ++first;
    }
    return result;
}

template <typename FwdIt>
uint32_t fromHex(FwdIt& first, FwdIt last,
                 size_t minLength = 1, size_t maxLength = SIZE_MAX)
{
    uint32_t result = 0;
    for (size_t i = 0; i < maxLength; ++i)
    {
        if (first == last && i < minLength)
            throw std::invalid_argument("Hexadecimal sequence is too short.");
        uint32_t tmp = *first;
        if ('0' <= tmp && tmp <= '9')
            result = result * 16 + tmp - '0';
        else if ('A' <= tmp && tmp <= 'F')
            result = result * 16 + tmp - 'A' + 10;
        else if ('a' <= tmp && tmp <= 'f')
            result = result * 16 + tmp - 'a' + 10;
        else if (i < minLength)
            throw std::invalid_argument("Hexadecimal sequence is too short.");
        else
            break;
        if (i == sizeof(result) * 2)
            throw std::invalid_argument("Hexadecimal sequence is too long.");
        ++first;
    }
    return result;
}

template <typename Char>
Char toCharDigit(Char c)
{
    return c + (c < 0xA ? '0' : 'A' - 10);
}

}}
