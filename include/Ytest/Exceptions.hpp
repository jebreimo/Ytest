//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <exception>
#include <utility>
#include <vector>
#include "Error.hpp"

namespace Ytest
{
    class Failure
    {
    public:
        Failure(const Failure&) = default;

        Failure(Failure&&) noexcept = default;

        virtual ~Failure() = default;

        Failure& operator=(const Failure&) = default;

        Failure& operator=(Failure&&) noexcept = default;

        const Error& error() const
        {
            return m_Error;
        }

        std::string what() const
        {
            return m_Error.text();
        }

        void addContext(const std::string& file,
                        unsigned lineNo,
                        const std::string& message)
        {
            m_Error.addContext(file, lineNo, message);
        }
    protected:
        Failure(Error error) noexcept
            : m_Error(std::move(error))
        {}
    private:
        Error m_Error;
        std::string m_What;
        std::vector<Error> m_Context;
    };

    class TestFailure : public Failure
    {
    public:
        TestFailure(const std::string& file,
                    unsigned lineNo,
                    const std::string& message) noexcept
            : Failure(Error(file, lineNo, message, Error::Failure))
        {}
    };

    class CriticalFailure : public Failure
    {
    public:
        CriticalFailure(const std::string& file,
                        unsigned lineNo,
                        const std::string& message) noexcept
            : Failure(Error(file, lineNo, message, Error::CriticalFailure))
        {}
    };

    class FatalFailure : public Failure
    {
    public:
        FatalFailure(const std::string& file,
                     unsigned lineNo,
                     const std::string& message) noexcept
            : Failure(Error(file, lineNo, message, Error::FatalFailure))
        {}
    };

    class UnhandledException : public Failure
    {
    public:
        UnhandledException(const std::string& file,
                           unsigned lineNo,
                           const std::string& message) noexcept
            : Failure(Error(file, lineNo, message, Error::UnhandledException))
        {}
    };
}
