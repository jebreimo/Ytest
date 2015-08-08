//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-28
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstddef>
#include <cstdint>

namespace Ystring
{

#ifdef _MSC_VER
#define WCHAR_IS_2_BYTES
#else
    static_assert(sizeof(wchar_t) == 4, "Size of wchar_t isn't 4 bytes.");
    #define WCHAR_IS_4_BYTES
#endif

template <size_t>
struct InternalCharType;

template <>
struct InternalCharType<1>
{
    typedef char Type;
};

template <>
struct InternalCharType<2>
{
    typedef uint16_t Type;
};

template <>
struct InternalCharType<4>
{
    typedef uint32_t Type;
};

template <typename T>
auto internal_char_type_cast(T* s)
        -> typename InternalCharType<sizeof(T)>::Type*
{
    typedef typename InternalCharType<sizeof(T)>::Type Type;
    return reinterpret_cast<Type*>(s);
}

template <typename T>
auto internal_char_type_cast(const T* s)
        -> const typename InternalCharType<sizeof(T)>::Type*
{
    typedef typename InternalCharType<sizeof(T)>::Type Type;
    return reinterpret_cast<const Type*>(s);
}

}
