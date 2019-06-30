//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "StringReference.hpp"

namespace Ystring { namespace Generic {

    template<typename Str, typename It1, typename It2>
    void appendJoin(StringReference<Str>& dst, It1 first, It1 last,
                    Range<It2> delimiter)
    {
        if (first == last)
            return;

        auto appender = dst.getAppender();
        appender.append(makeRange(*first));
        while (++first != last)
        {
            appender.append(delimiter);
            appender.append(makeRange(*first));
        }
        dst.terminate();
    }

    template<typename Str, typename It>
    void appendJoin(StringReference<Str>& dst, It first, It last)
    {
        auto appender = dst.getAppender();
        for (; first != last; ++first)
            appender.append(makeRange(*first));
        dst.terminate();
    }

    template<typename Str, typename It1, typename It2>
    Str join(It1 first, It1 last, Range<It2> delimiter)
    {
        auto result = Str();
        auto ref = makeStringReference(result);
        appendJoin(ref, first, last, delimiter);
        return result;
    }

    template<typename Str, typename It>
    Str join(It first, It last)
    {
        auto result = Str();
        auto ref = makeStringReference(result);
        appendJoin(ref, first, last);
        return result;
    }
}}
