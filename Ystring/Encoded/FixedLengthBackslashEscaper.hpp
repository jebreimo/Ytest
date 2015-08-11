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

class FixedLengthBackslashEscaper
{
public:
    FixedLengthBackslashEscaper(uint32_t unicodeChar,
                                int unicodeHexDigits)
        : m_UnicodeChar(unicodeChar),
          m_MaxChar(unicodeHexDigits >= 8 ?
                    ~0u : (1u << (unicodeHexDigits * 4u)) - 1u),
          m_UnicodeHexDigits(unicodeHexDigits)
    {}

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
                if (chr > m_MaxChar)
                {
                    YSTRING_THROW(
                            "Character " + std::to_string(int64_t(chr)) +
                            " has more than " +
                            std::to_string(int64_t(m_UnicodeHexDigits)) +
                            " hex digits.");
                }
                dst.append(m_UnicodeChar);
                for (auto i = 0; i < m_UnicodeHexDigits; ++i)
                {
                    auto shift = (m_UnicodeHexDigits - i - 1) * 4;
                    dst.append(toCharDigit((chr >> shift) & 0xF));
                }
            }
            break;
        }
    }
private:
    uint32_t m_UnicodeChar;
    uint32_t m_MaxChar;
    int m_UnicodeHexDigits;
};

}}
