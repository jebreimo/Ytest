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
RndIt findUpperBound(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    while (beg != end)
    {
        RndIt mid = beg + std::distance(beg, end) / 2;
        if (value < keyFunc(*mid))
            end = mid;
        else
            beg = mid + 1;
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

template <typename RndIt, typename T, typename UnaryFunc>
bool binarySearch(RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt it = findLowerBound(beg, end, value, keyFunc);
    return it != end && value == keyFunc(*it);
}

template <typename RndIt, typename T, typename UnaryFunc>
std::pair<RndIt, RndIt> findBounds(
        RndIt beg, RndIt end, const T& value, UnaryFunc keyFunc)
{
    RndIt first = findLowerBound(beg, end, value, keyFunc);
    RndIt second = findUpperBound(first, end, value, keyFunc);
    return std::make_pair(first, second);
}

template <typename UnaryFunc>
class KeyComparer
{
public:
    KeyComparer(UnaryFunc keyFunc) : m_KeyFunc(keyFunc) {}
    template <typename T>
    bool operator()(T a, T b) {return m_KeyFunc(a) < m_KeyFunc(b);}
private:
    UnaryFunc m_KeyFunc;
};

template <typename RndIt, typename UnaryFunc>
void sortByKey(RndIt beg, RndIt end, UnaryFunc keyFunc)
{
    std::sort(beg, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
FwdIt getMaxElement(FwdIt begin, FwdIt end, UnaryFunc keyFunc)
{
    return std::max_element(begin, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
FwdIt getMinElement(FwdIt begin, FwdIt end, UnaryFunc keyFunc)
{
    return std::min_element(begin, end, KeyComparer<UnaryFunc>(keyFunc));
}

template <typename FwdIt, typename UnaryFunc>
std::pair<FwdIt, FwdIt> getMinmaxElement(
        FwdIt begin, FwdIt end, UnaryFunc keyFunc)
{
    return std::minmax_element(begin, end, KeyComparer<UnaryFunc>(keyFunc));
}

}}
