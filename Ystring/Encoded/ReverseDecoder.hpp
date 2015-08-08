//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include "../Generic/Range.hpp"

namespace Ystring { namespace Encoded {

template <typename BiIt, typename Encoding>
class ReverseDecoder
{
public:
    static const bool isForward = false;

    ReverseDecoder(BiIt first, BiIt last, Encoding encoding)
        : m_First(first),
          m_Last(last),
          m_Encoding(encoding)
    {}

    bool next(uint32_t& ch)
    {
        return m_Encoding.prev(ch, m_First, m_Last);
    }

    bool skip()
    {
        return m_Encoding.skipPrev(m_First, m_Last);
    }

    const Encoding& getEncoding() const
    {
        return m_Encoding;
    }

    BiIt getLogicalBegin()
    {
        return m_Last;
    }

    void setLogicalBegin(BiIt first)
    {
        m_Last = first;
    }

    BiIt getLogicalEnd()
    {
        return m_First;
    }

    void setLogicalEnd(BiIt last)
    {
        m_First = last;
    }

    Generic::Range<BiIt> getRange() const
    {
        return Generic::makeRange(m_First, m_Last);
    }

    BiIt begin() const
    {
        return m_First;
    }

    BiIt end() const
    {
        return m_Last;
    }

protected:
    BiIt m_First;
    BiIt m_Last;
    Encoding m_Encoding;
};

template <typename BiIt, typename Encoding>
ReverseDecoder<BiIt, Encoding> makeReverseDecoder(
        BiIt first,
        BiIt last,
        Encoding encoding)
{
    return ReverseDecoder<BiIt, Encoding>(first, last, encoding);
}

template <typename BiIt, typename Encoding>
ReverseDecoder<BiIt, Encoding> makeReverseDecoder(
        Generic::Range<BiIt> range,
        Encoding encoding)
{
    return ReverseDecoder<BiIt, Encoding>(range.begin(), range.end(),
                                          encoding);
}

template <typename BiIt, typename Encoding>
bool empty(const ReverseDecoder<BiIt, Encoding>& dec)
{
    return dec.begin() == dec.end();
}

}}
