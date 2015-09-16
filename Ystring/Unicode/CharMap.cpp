//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CharMap.hpp"

#include <cassert>
#include "../Utilities/KeyFunctionAlgorithms.hpp"

namespace Ystring { namespace Unicode
{
    uint32_t segment(const CompactCharMapping& ccs)
    {
        return ccs.segment;
    }

    uint32_t key(const CharMapping& mapping)
    {
        return mapping.chr;
    }

    static const uint32_t SegMask = ~(uint32_t)0x1F;

    CharMap::CharMap(const CompactCharMapping* compactMappings,
                     size_t compactMappingsSize,
                     const CharMapping* mappings,
                     size_t mappingsSize)
        : m_CompactMappings(compactMappings),
          m_Mappings(mappings),
          m_CompactMappingsSize(compactMappingsSize),
          m_MappingsSize(mappingsSize)
    {
        assert(compactMappings);
        assert(mappings || mappingsSize == 0);
        assert(compactMappingsSize != 0);
        assert(compactMappings[0].segment < 0x80);
        assert(compactMappingsSize == 1 ||
                       compactMappings[1].segment >= 0x80);
        initializeFastMapping();
    }

    uint32_t CharMap::get(uint32_t chr) const
    {
        if (chr < 64)
            return chr;
        if (chr < FAST_MAPPING_MAX)
            return m_FastMapping[chr - 64];

        uint32_t mappedChr = chr;
        if (findInCompactMapping(chr, mappedChr) ||
                findInMapping(chr, mappedChr))
        {
            return mappedChr;
        }

        return chr;
    }

    bool CharMap::has(uint32_t chr) const
    {
        uint32_t mappedChr = chr;
        return findInCompactMapping(chr, mappedChr) ||
               findInMapping(chr, mappedChr);
    }

    bool CharMap::findInCompactMapping(uint32_t chr,
                                       uint32_t& mappedChr) const
    {
        const CompactCharMapping* set = Utilities::findLowerBound(
                    m_CompactMappings,
                    m_CompactMappings + m_CompactMappingsSize,
                    chr & SegMask,
                    segment);
        if (set == m_CompactMappings + m_CompactMappingsSize ||
            set->segment != (chr & SegMask))
            return false;

        return set->get(chr, mappedChr);
    }

    bool CharMap::findInMapping(uint32_t chr, uint32_t& mappedChr) const
    {
        const CharMapping* mapping = Utilities::findLowerBound(
                    m_Mappings,
                    m_Mappings + m_MappingsSize,
                    chr,
                    key);
        if (mapping == m_Mappings + m_MappingsSize || mapping->chr != chr)
            return false;

        mappedChr = mapping->mappedChr;
        return true;
    }

    void CharMap::initializeFastMapping()
    {
        for (uint16_t i = 0; i < FAST_MAPPING_SIZE; ++i)
            m_FastMapping[i] = i + 64;
        for (size_t i = 0; i < m_CompactMappingsSize; ++i)
        {
            auto& mapping = m_CompactMappings[i];
            auto j = mapping.segment - 64;
            if (j >= FAST_MAPPING_SIZE)
                break;
            auto mask = mapping.affected;
            while (j < FAST_MAPPING_SIZE && mask)
            {
                if (mask & 1)
                    m_FastMapping[j] += uint16_t(mapping.offset);
                mask >>= 1;
                ++j;
            }
        }
        for (size_t i = 0; i < m_MappingsSize; ++i)
        {
            if (m_Mappings[i].chr > FAST_MAPPING_MAX)
                break;
            m_FastMapping[m_Mappings[i].chr - 64] =
                    uint16_t(m_Mappings[i].mappedChr);
        }
    }
}}
