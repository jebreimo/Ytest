//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CaseConverter.hpp"

#include <type_traits>
#include "CharMap.hpp"
#include "StandardUpperCase.hpp"

namespace Ystring { namespace Unicode
{
    namespace
    {
        CharMap g_UpperMap(
                CompactUpperCaseMappings,
                std::extent<decltype(CompactUpperCaseMappings), 0>::value,
                UpperCaseMappings,
                std::extent<decltype(UpperCaseMappings), 0>::value);
    }


    uint32_t upper(uint32_t ch)
    {
        return g_UpperMap.get(ch);
    }
}}
