//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <map>
#include <vector>
#include "CharMappingTypes.hpp"

namespace Ystring { namespace Unicode {

class CharMap
{
public:
    CharMap(const CompactCharMapping* compactMappings,
            size_t compactMappingsSize,
            const CharMapping* mappings,
            size_t mappingsSize);

    uint32_t get(uint32_t chr) const;
    bool has(uint32_t chr) const;
private:
    bool findInCompactMapping(uint32_t chr, uint32_t& mappedChr) const;
    bool findInMapping(uint32_t chr, uint32_t& mappedChr) const;

    const CompactCharMapping* m_CompactMappings;
    const CharMapping* m_Mappings;
    size_t m_CompactMappingsSize;
    size_t m_MappingsSize;
};

}}
