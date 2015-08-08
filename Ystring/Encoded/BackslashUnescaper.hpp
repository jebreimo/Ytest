//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdexcept>
#include "../Generic/Range.hpp"
#include "../Utilities/Utilities.hpp"

namespace Ystring { namespace Encoded {

class BackslashUnescaper
{
public:
    BackslashUnescaper(bool supportsOctals)
        : m_SupportsOctals(supportsOctals)
    {}

    template <typename It>
    bool unescape(uint32_t& result, It& first, It last)
    {
        if (first == last || *first != '\\')
            return false;
        if (++first == last)
            YSTRING_THROW(
                    "Incomplete escape sequence at end of string.");
        auto escape = *first++;
        switch (escape)
        {
        case 'U': result = Utilities::fromHex(first, last, 8, 8); break;
        case 'a': result = '\a'; break;
        case 'b': result = '\b'; break;
        case 'f': result = '\f'; break;
        case 'n': result = '\n'; break;
        case 'r': result = '\r'; break;
        case 't': result = '\t'; break;
        case 'v': result = '\v'; break;
        case 'u': result = Utilities::fromHex(first, last, 4, 4); break;
        case 'x': result = Utilities::fromHex(first, last, 2, 2); break;
        default:
            if (m_SupportsOctals && '0' <= escape && escape <= '7')
            {
                --first;
                result = Utilities::fromOct(first, last, 1, 3);
            }
            else
            {
                result = escape;
            }
            break;
        }
        return true;
    }
private:
    bool m_SupportsOctals;
};

}}
