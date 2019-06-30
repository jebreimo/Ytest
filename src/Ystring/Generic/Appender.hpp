//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-17
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <string>
#include "../YstringException.hpp"
#include "../Utilities/Algorithms.hpp"
#include "Range.hpp"

namespace Ystring { namespace EncodedString
{
    template <typename StringT>
    class Appender
    {
    public:
        typedef StringT String;
        typedef typename String::value_type ValueType;

        Appender(String& str)
            : m_String(str)
        {}

        template <typename It>
        Appender& append(Generic::Range<It> str)
        {
            m_String.insert(end(m_String), str.begin(), str.end());
            return *this;
        }

        Appender& append(ValueType c)
        {
            m_String.push_back(c);
            return *this;
        }
    private:
        String& m_String;
    };

    template <typename CharT>
    class Appender<CharT*>
    {
    public:
        typedef CharT* String;
        typedef CharT ValueType;

        Appender(ValueType* str, size_t* size, size_t capacity)
            : m_String(str),
              m_Size(size),
              m_Capacity(capacity)
        {}

        template <typename It>
        Appender& append(Generic::Range<It> str)
        {
            auto its = Utilities::copy(
                    str.begin(), str.end(),
                    &m_String[*m_Size], &m_String[m_Capacity]);
            if (its.second == &m_String[m_Capacity])
            {
                m_String[m_Capacity - 1] = 0;
                YSTRING_THROW("Attempt to write beyond the end of string.");
            }
            *m_Size = its.second - m_String;
            return *this;
        }

        Appender& append(ValueType c)
        {
            if (*m_Size + 1 >= m_Capacity)
            {
                YSTRING_THROW("Attempt to write beyond the end of string.");
            }
            *m_Size++ = c;
            return *this;
        }
    private:
        String m_String;
        size_t* m_Size;
        size_t m_Capacity;
    };
}}
