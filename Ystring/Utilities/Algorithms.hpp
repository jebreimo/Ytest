//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01.
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

namespace Ystring { namespace Utilities
{
    template <typename InpIt, typename OutIt>
    std::pair<InpIt, OutIt> copy(InpIt srcBeg, InpIt srcEnd,
                                 OutIt dstBeg, OutIt dstEnd)
    {
        while (srcBeg != srcEnd && dstBeg != dstEnd)
            *dstBeg++ = *srcBeg++;
        return std::make_pair(srcBeg, dstBeg);
    }

    template <typename InpIt1, typename InpIt2>
    std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
                                       InpIt2 cmpBeg, InpIt2 cmpEnd)
    {
        while (beg != end && cmpBeg != cmpEnd && *beg == *cmpBeg)
        {
            ++beg;
            ++cmpBeg;
        }
        return std::make_pair(beg, cmpBeg);
    }

    template <typename InpIt1, typename InpIt2, typename BinaryPredicate>
    std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
                                       InpIt2 cmpBeg, InpIt2 cmpEnd,
                                       BinaryPredicate pred)
    {
        while (beg != end && cmpBeg != cmpEnd && pred(*beg, *cmpBeg))
        {
            beg++;
            cmpBeg++;
        }
        return std::make_pair(beg, cmpBeg);
    }

    template <typename FwdIt1, typename FwdIt2>
    std::pair<FwdIt1, FwdIt1> search(FwdIt1 beg, FwdIt1 end,
                                     FwdIt2 cmpBeg, FwdIt2 cmpEnd)
    {
        if (cmpBeg == cmpEnd)
            return std::make_pair(end, end);
        while (beg != end)
        {
            auto its = Utilities::mismatch(beg, end, cmpBeg, cmpEnd);
            if (its.second == cmpEnd)
                return std::make_pair(beg, its.first);
            else if (its.first == end)
                break;
            ++beg;
        }
        return std::make_pair(end, end);
    }

    template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
    std::pair<FwdIt1, FwdIt1> searchLastImpl(FwdIt1 beg, FwdIt1 end,
                                             FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                             BinaryPredicate pred,
                                             std::forward_iterator_tag)
    {
        std::pair<FwdIt1, FwdIt1> result(end, end);
        if (cmpBeg == cmpEnd)
            return result;
        while (beg != end)
        {
            auto its = Utilities::mismatch(beg, end, cmpBeg, cmpEnd, pred);
            if (its.second == cmpEnd)
                result = std::make_pair(beg, its.first);
            ++beg;
        }
        return result;
    }

    template <typename BiIt, typename FwdIt, typename BinaryPredicate>
    std::pair<BiIt, BiIt> searchLastImpl(BiIt beg, BiIt end,
                                         FwdIt cmpBeg, FwdIt cmpEnd,
                                         BinaryPredicate pred,
                                         std::bidirectional_iterator_tag)
    {
        if (cmpBeg == cmpEnd)
            return std::make_pair(end, end);
        BiIt it = end;
        while (it != beg)
        {
            --it;
            auto its = Utilities::mismatch(it, end, cmpBeg, cmpEnd, pred);
            if (its.second == cmpEnd)
                return std::make_pair(it, its.first);
        }
        return std::make_pair(it, it);
    }

    template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
    std::pair<FwdIt1, FwdIt1> searchLast(FwdIt1 beg, FwdIt1 end,
                                         FwdIt2 cmpBeg, FwdIt2 cmpEnd,
                                         BinaryPredicate pred)
    {
        return searchLastImpl(
                beg, end,
                cmpBeg, cmpEnd,
                pred,
                typename std::iterator_traits<FwdIt1>::iterator_category());
    }

    template <typename FwdIt1, typename FwdIt2>
    std::pair<FwdIt1, FwdIt1> searchLast(FwdIt1 beg, FwdIt1 end,
                                         FwdIt2 cmpBeg, FwdIt2 cmpEnd)
    {
        return searchLast(
                beg, end,
                cmpBeg, cmpEnd,
                std::equal_to<
                        typename std::iterator_traits<FwdIt1>::value_type>());
    }
}}
