//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-06
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>

namespace Ystring { namespace Utilities {

template <typename OutputIt>
class ArrayOutputIterator : public std::iterator<
        std::output_iterator_tag,
        typename std::iterator_traits<OutputIt>::value_type,
        typename std::iterator_traits<OutputIt>::difference_type,
        typename std::iterator_traits<OutputIt>::pointer,
        typename std::iterator_traits<OutputIt>::reference>
{
public:
    typedef typename std::iterator_traits<OutputIt>::value_type Value;

    ArrayOutputIterator(OutputIt it, size_t* size, size_t capacity)
        : m_It(it),
          m_Size(size),
          m_Capacity(capacity)
    {}

    ArrayOutputIterator& operator=(const Value& value)
    {
        if (*m_Size == m_Capacity)
            YSTRING_THROW(
                    "Attempt to write after the final iterator position.");
        *m_It = value;
        ++*m_Size;
        return *this;
    }

    ArrayOutputIterator& operator*()
    {
        return *this;
    }

    ArrayOutputIterator& operator++()
    {
        return *this;
    }
private:
    OutputIt m_It;
    size_t* m_Size;
    size_t m_Capacity;
};

}}
