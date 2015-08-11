//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdint.h>
#include "../Utilities/Utilities.hpp"

namespace Ystring { namespace Encoded {

class XmlEscaper
{
public:
    template <typename Appender>
    void escape(Appender dst, uint32_t chr)
    {
        using Utilities::toCharDigit;
        dst.append('&');
        switch (chr)
        {
        case '"': dst.append('q').append('u').append('o').append('t'); break;
        case '&': dst.append('a').append('m').append('p'); break;
        case '\'': dst.append('a').append('p').append('o').append('s'); break;
        case '<': dst.append('l').append('t'); break;
        case '>': dst.append('g').append('t'); break;
        default:
            {
                dst.append('#').append('x');
                auto digits = Utilities::countHexDigits(chr);
                for (auto i = 0; i < digits; ++i)
                {
                    auto shift = (digits - i - 1) * 4;
                    dst.append(toCharDigit((chr >> shift) & 0xF));
                }
            }
            break;
        }
        dst.append(';');
    }
};

}}
