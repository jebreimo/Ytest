//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-27
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Iso8859_1.hpp"

#include <vector>

namespace Ystring { namespace CodePage {

const uint32_t* iso8859_1ToUnicode()
{
    static std::vector<uint32_t> table;
    if (table.empty())
    {
        table.resize(256);
        for (uint32_t i = 0; i < 256; ++i)
            table[i] = i;
    }
    return &table[0];
}

std::pair<const std::pair<uint32_t, uint8_t>*,
          const std::pair<uint32_t, uint8_t>*> unicodeToIso8859_1()
{
    return std::pair<const std::pair<uint32_t, uint8_t>*,
                     const std::pair<uint32_t, uint8_t>*>(nullptr,
                                                          nullptr);
}

CodePage makeIso8859_1()
{
    auto to = iso8859_1ToUnicode();
    auto from = unicodeToIso8859_1();
    return CodePage(to, from.first, from.second, Encoding::ISO_8859_1);
}

}}
