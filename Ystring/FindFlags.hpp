//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

namespace Ystring {

struct FindFlags
{
    enum Type
    {
        DEFAULTS = 0,
        CASE_INSENSITIVE = 1
    };
    typedef unsigned Flags;

    static bool isCaseInsensitive(Flags flags)
    {
        return (flags & CASE_INSENSITIVE) != 0;
    }
};

typedef FindFlags::Flags FindFlags_t;

}
