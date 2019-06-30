//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ios>

namespace Ytest
{
    class StreamRedirection
    {
    public:
        StreamRedirection(std::ios& stream, std::ios& replacement);
        StreamRedirection(std::ios& stream, std::streambuf* replacement);
        StreamRedirection(StreamRedirection&& other);
        ~StreamRedirection();
    private:
        std::ios& m_Stream;
        std::streambuf* m_OriginalBuffer;
    };
}
