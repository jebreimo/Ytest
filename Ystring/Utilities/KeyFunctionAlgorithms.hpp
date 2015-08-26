//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>

/** @file
  * @brief Defines various wrappers and extensions to the generic algorithms
  *     in the standard library's algorithm header.
  */

namespace Ystring { namespace Utilities {

template <typename RndIt, typename T, typename UnaryFunc>
RndIt findLowerBound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    while (beg != end)
    {
        RndIt mid = beg + std::distance(beg, end) / 2;
        if (keyFunc(*mid) < value)
            beg = mid + 1;
        else
            end = mid;
    }
    return beg;
}

template <typename RndIt, typename T, typename UnaryFunc>
RndIt binaryFind(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt it = findLowerBound(beg, end, value, keyFunc);
    if (it == end || value < keyFunc(*it))
      return end;
    return it;
}

}}
