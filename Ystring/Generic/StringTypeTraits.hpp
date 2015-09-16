//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <string>
#include "StringReference.hpp"

namespace Ystring { namespace Generic
{
    template <typename Enc1, typename Enc2>
    struct SameEncoding
        : std::integral_constant<bool, Enc1::encoding == Enc2::encoding>
    {};

    template <typename It1, typename It2>
    struct SameIteratorValueType
        : std::is_same<typename std::iterator_traits<It1>::value_type,
                       typename std::iterator_traits<It2>::value_type>
    {};

    template <typename It1, typename Enc1,
              typename It2, typename Enc2>
    struct CanCompareRawValues
        : std::integral_constant<bool,
                                 SameEncoding<Enc1, Enc2>::value &&
                                    SameIteratorValueType<It1, It2>::value>
    {};

    template <typename Char1, typename Enc1,
              typename Char2, typename Enc2>
    struct CanCopyRawValues
        : std::integral_constant<bool,
                                 SameEncoding<Enc1, Enc2>::value &&
                                    std::is_same<Char1, Char2>::value>
    {};

    template <typename Str>
    struct IsByteString
        : std::integral_constant<
                bool, sizeof(typename StringReference<Str>::ValueType) == 1>
    {};
}}
