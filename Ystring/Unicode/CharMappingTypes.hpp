//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <utility>
#include "../YstringDefinitions.hpp"

namespace Ystring { namespace Unicode
{
    struct YSTRING_API CompactCharMapping
    {
        uint32_t segment;
        uint32_t offset;
        uint32_t affected;
        uint32_t ignorable;

        bool get(uint32_t chr, uint32_t& mappedChr) const;
    };

    struct CharMapping
    {
        uint32_t chr;
        uint32_t mappedChr;
    };
}}
