//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-08
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iterator>

namespace Ystring { namespace Utilities {

template <typename Value>
class CountingOutputIterator : public std::iterator<
        std::output_iterator_tag,
        Value>
{
public:
    explicit CountingOutputIterator(size_t* count)
        : m_Count(count)
    {}

    CountingOutputIterator& operator=(const Value& value)
    {
        ++*m_Count;
        return *this;
    }

    CountingOutputIterator& operator*()
    {
        return *this;
    }

    CountingOutputIterator& operator++()
    {
        return *this;
    }

    CountingOutputIterator& operator++(int)
    {
        return *this;
    }
private:
    size_t* m_Count;
};

}}
