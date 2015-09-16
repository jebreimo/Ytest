//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Utilities/Algorithms.hpp"
#include "Range.hpp"

namespace Ystring { namespace Generic
{
    template <typename FwdIt, typename OutIt>
    OutIt copy(Range<FwdIt> src, OutIt dst)
    {
        return std::copy(begin(src), end(src), dst);
    }

    template <typename FwdIt, typename Value>
    FwdIt find(Range<FwdIt> range, const Value& value)
    {
        return std::find(begin(range), end(range), value);
    }

    template <typename FwdIt1, typename FwdIt2>
    std::pair<FwdIt1, FwdIt2> mismatch(Range<FwdIt1> range1,
                                       Range<FwdIt2> range2)
    {
        return Utilities::mismatch(begin(range1), end(range1),
                                   begin(range2), end(range2));
    }

    template <typename FwdIt1, typename FwdIt2>
    Range<FwdIt1> search(Range<FwdIt1> range1, Range<FwdIt2> range2)
    {
        return Utilities::search(begin(range1), end(range1),
                                 begin(range2), end(range2));
    }

    template <typename FwdIt1, typename FwdIt2>
    Range<FwdIt1> searchLast(Range<FwdIt1> range1, Range<FwdIt2> range2)
    {
        return Utilities::searchLast(begin(range1), end(range1),
                                     begin(range2), end(range2));
    }
}}
