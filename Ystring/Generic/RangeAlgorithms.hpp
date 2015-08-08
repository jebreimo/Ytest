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

namespace Ystring { namespace Generic {

//template <typename FwdIt1, typename FwdIt2>
//auto compare(Range<FwdIt1> range1, Range<FwdIt2> range2)
//    -> decltype(*range1.begin() - *range2.begin())
//{
//    return Utilities::compare(begin(range1), end(range1),
//                               begin(range2), end(range2));
//}
//
//template <typename FwdIt1, typename FwdIt2, typename BinaryFunc>
//auto compare(Range<FwdIt1> range1, Range<FwdIt2> range2,
//             BinaryFunc cmp)
//    -> decltype(cmp(*begin(range1), *begin(range2)))
//{
//    return Utilities::compare(begin(range1), end(range1),
//                               begin(range2), end(range2),
//                               cmp);
//}

template <typename FwdIt, typename OutIt>
OutIt copy(Range<FwdIt> src, OutIt dst)
{
    return std::copy(begin(src), end(src), dst);
}

//template <typename FwdIt, typename T>
//size_t count(Range<FwdIt> range, const T& value)
//{
//    return std::count(begin(range), end(range), value);
//}
//
//template <typename FwdIt, typename UnaryPred>
//size_t countIf(Range<FwdIt> range, UnaryPred pred)
//{
//    return std::count_if(begin(range), end(range), pred);
//}
//
//template <typename FwdIt1, typename FwdIt2>
//bool equal(Range<FwdIt1> range1, Range<FwdIt2> range2)
//{
//    return Utilities::equal(begin(range1), end(range1),
//                             begin(range2), end(range2));
//}
//
//template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
//bool equal(Range<FwdIt1> range1, Range<FwdIt2> range2,
//           BinaryPred predicate)
//{
//    return Utilities::equal(begin(range1), end(range1),
//                             begin(range2), end(range2),
//                             predicate);
//}

template <typename FwdIt, typename Value>
FwdIt find(Range<FwdIt> range, const Value& value)
{
    return std::find(begin(range), end(range), value);
}

//template <typename FwdIt, typename UnaryPred>
//FwdIt find_if(Range<FwdIt> range, UnaryPred predicate)
//{
//    return std::find_if(begin(range), end(range), predicate);
//}
//
//template <typename FwdIt, typename UnaryPred>
//FwdIt find_if_not(Range<FwdIt> range, UnaryPred predicate)
//{
//    return std::find_if_not(begin(range), end(range), predicate);
//}
//
//template <typename BiIt, typename UnaryPred>
//BiIt findEndIf(Range<BiIt> range, UnaryPred predicate)
//{
//    return Utilities::findEndIf(begin(range), end(range), predicate);
//}
//
//template <typename BiIt, typename UnaryPred>
//BiIt findEndIfNot(Range<BiIt> range, UnaryPred predicate)
//{
//    return Utilities::findEndIfNot(begin(range), end(range), predicate);
//}
//
//template <typename BiIt, typename Value>
//BiIt findLast(Range<BiIt> range, const Value& value)
//{
//    return Utilities::findLast(begin(range), end(range), value);
//}
//
//template <typename BiIt, typename UnaryPred>
//BiIt findLastIf(Range<BiIt> range, UnaryPred predicate)
//{
//    return Utilities::findLastIf(begin(range), end(range), predicate);
//}
//
//template <typename BiIt, typename UnaryPred>
//BiIt findLastIfNot(Range<BiIt> range, UnaryPred predicate)
//{
//    return Utilities::findLastIfNot(begin(range), end(range), predicate);
//}
//
//template <typename FwdIt1, typename FwdIt2>
//FwdIt1 findFirstOf(Range<FwdIt1> range, Range<FwdIt2> values)
//{
//    return std::find_first_of(begin(range), end(range),
//                              begin(values), end(values));
//}
//
//template <typename FwdIt1, typename FwdIt2>
//FwdIt1 findLastOf(Range<FwdIt1> range, Range<FwdIt2> values)
//{
//    return Utilities::findLastOf(begin(range), end(range),
//                                  begin(values), end(values));
//}
//
//template <typename FwdIt, typename Value>
//bool has(Range<FwdIt> range, const Value& value)
//{
//    return find(range, value) != end(range);
//}
//
//template <typename FwdIt1, typename FwdIt2>
//bool less(Range<FwdIt1> range1, Range<FwdIt2> range2)
//{
//    return Utilities::less(begin(range1), end(range1),
//                            begin(range2), end(range2));
//}
//
//template <typename FwdIt1, typename FwdIt2,
//          typename BinaryPredicate1, typename BinaryPredicate2>
//bool less(Range<FwdIt1> range1, Range<FwdIt2> range2,
//          BinaryPredicate1 isEqual,
//          BinaryPredicate2 isLess)
//{
//    return Utilities::less(begin(range1), end(range1),
//                           begin(range2), end(range2),
//                           isEqual, isLess);
//}

template <typename FwdIt1, typename FwdIt2>
std::pair<FwdIt1, FwdIt2> mismatch(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Utilities::mismatch(begin(range1), end(range1),
                               begin(range2), end(range2));
}

//template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
//std::pair<FwdIt1, FwdIt2> mismatch(Range<FwdIt1> range1, Range<FwdIt2> range2,
//                                   BinaryPred predicate)
//{
//    return Utilities::mismatch(begin(range1), end(range1),
//                                begin(range2), end(range2),
//                                predicate);
//}

template <typename FwdIt1, typename FwdIt2>
Range<FwdIt1> search(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Utilities::search(begin(range1), end(range1),
                             begin(range2), end(range2));
}

//template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
//Range<FwdIt1> search(Range<FwdIt1> range1, Range<FwdIt2> range2,
//                     BinaryPred predicate)
//{
//    return Utilities::search(begin(range1), end(range1),
//                             begin(range2), end(range2),
//                             predicate);
//}

template <typename FwdIt1, typename FwdIt2>
Range<FwdIt1> searchLast(Range<FwdIt1> range1, Range<FwdIt2> range2)
{
    return Utilities::searchLast(begin(range1), end(range1),
                                 begin(range2), end(range2));
}

//template <typename FwdIt1, typename FwdIt2, typename BinaryPred>
//Range<FwdIt1> searchLast(Range<FwdIt1> range1, Range<FwdIt2> range2,
//                         BinaryPred predicate)
//{
//    return Utilities::searchLast(begin(range1), end(range1),
//                                 begin(range2), end(range2),
//                                 predicate);
//}
//
//template <typename InIt, typename OutIt, typename UnaryFunc>
//OutIt transform(Range<InIt> range, OutIt dst, UnaryFunc func)
//{
//    return std::transform(begin(range), end(range), dst, func);
//}

}}
