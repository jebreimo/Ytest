//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-20
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Utilities/Utilities.hpp"

namespace Ystring { namespace Encoded {

class VariableLengthBackslashEscaper
{
public:
    template <typename Appender>
    void escape(Appender dst, uint32_t chr)
    {
        using Utilities::toCharDigit;
        dst.append('\\');
        switch (chr)
        {
        case '\a': dst.append('a'); break;
        case '\b': dst.append('b'); break;
        case '\t': dst.append('t'); break;
        case '\n': dst.append('n'); break;
        case '\v': dst.append('v'); break;
        case '\f': dst.append('f'); break;
        case '\r': dst.append('r'); break;
        case '\"': dst.append('"'); break;
        case '\\': dst.append('\\'); break;
        default:
            {
                int shifts;
                if (chr < 256)
                {
                    dst.append('x');
                    shifts = 2;
                }
                else if (chr < 0x10000)
                {
                    dst.append('u');
                    shifts = 4;
                }
                else
                {
                    dst.append('U');
                    shifts = 8;
                }
                for (auto i = 0; i < shifts; ++i)
                {
                    auto shift = (shifts - i - 1) * 4;
                    dst.append(toCharDigit((chr >> shift) & 0xF));
                }
            }
            break;
        }
    }
};

}}
