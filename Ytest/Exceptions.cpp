//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Exceptions.hpp"

namespace Ytest
{
    AbstractFailure::AbstractFailure(const Error& error)
        : m_Error(error)
    {}

    AbstractFailure::~AbstractFailure()
    {}

    const Error& AbstractFailure::error() const
    {
        return m_Error;
    }

    std::string AbstractFailure::what() const
    {
        return m_Error.text();
    }

    void AbstractFailure::addContext(const std::string& file,
                                     unsigned lineNo,
                                     const std::string& message)
    {
        m_Error.addContext(file, lineNo, message);
    }

    TestFailure::TestFailure(const std::string& file,
                             unsigned lineNo,
                             const std::string& message)
        : AbstractFailure(Error(file, lineNo, message, Error::Failure))
    {}

    TestFailure::~TestFailure()
    {}

    CriticalFailure::CriticalFailure(const std::string& file,
                                     unsigned lineNo,
                                     const std::string& message)
        : AbstractFailure(Error(file, lineNo, message,
                                Error::CriticalFailure))
    {}

    CriticalFailure::~CriticalFailure()
    {}

    FatalFailure::FatalFailure(const std::string& file,
                               unsigned lineNo,
                               const std::string& message)
        : AbstractFailure(Error(file, lineNo, message, Error::FatalFailure))
    {}

    FatalFailure::~FatalFailure()
    {}
}
