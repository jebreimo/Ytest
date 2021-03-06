//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iterator>
#include "Appender.hpp"
#include "Encoder.hpp"

namespace Ystring { namespace Generic
{
    template <typename String>
    class StringReference
    {
    public:
        typedef typename String::value_type ValueType;
        typedef std::back_insert_iterator<String> BackInsertIterator;

        StringReference(String& str)
            : m_String(str)
        {}

        EncodedString::Appender<String> getAppender()
        {
            return EncodedString::Appender<String>(m_String);
        }

        template <typename Enc>
        EncodedString::Encoder<BackInsertIterator, Enc> getEncoder(Enc encoding)
        {
            return EncodedString::makeEncoder(std::back_inserter(m_String),
                                              encoding);
        }

        void reserve(size_t size)
        {
            if (size)
                m_String.reserve(m_String.size() + size);
        }

        void terminate()
        {}
    private:
        String& m_String;
    };

    template <typename T>
    StringReference<T> makeStringReference(T& str)
    {
        using namespace std;
        return StringReference<T>(str);
    }

}}
