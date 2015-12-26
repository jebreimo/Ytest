//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <exception>
#include <vector>
#include "Error.hpp"

namespace Ytest
{
    class AbstractFailure
    {
    public:
        virtual ~AbstractFailure();
        const Error& error() const;
        std::string what() const;
        void addContext(const std::string& file,
                        unsigned lineNo,
                        const std::string& message);
    protected:
        AbstractFailure(const Error& error);
    private:
        Error m_Error;
        std::string m_What;
        std::vector<Error> m_Context;
    };

    class TestFailure : public AbstractFailure
    {
    public:
        TestFailure(const std::string& file,
                    unsigned lineNo,
                    const std::string& message);
        ~TestFailure();
    };

    class CriticalFailure : public AbstractFailure
    {
    public:
        CriticalFailure(const std::string& file,
                        unsigned lineNo,
                        const std::string& message);
        ~CriticalFailure();
    };

    class FatalFailure : public AbstractFailure
    {
    public:
        FatalFailure(const std::string& file,
                     unsigned lineNo,
                     const std::string& message);
        ~FatalFailure();
    };

    class UnhandledException : public AbstractFailure
    {
    public:
        UnhandledException(const std::string& file,
                           unsigned lineNo,
                           const std::string& message);

        ~UnhandledException();
    };
}
