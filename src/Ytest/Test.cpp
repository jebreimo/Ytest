//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Test.hpp"

#include <algorithm>
#include <utility>
#include <stdexcept>

namespace Ytest
{
    Test::Test(std::string  name)
        : m_Assertions(0),
          m_Name(std::move(name)),
          m_StartTime(0),
          m_EndTime(0)
    {}

    size_t Test::assertions() const
    {
        return m_Assertions;
    }

    void Test::incrementAssertions()
    {
        m_Assertions++;
    }

    bool Test::failed() const
    {
        return !m_Errors.empty() && m_Errors.back().type() != Error::None;
    }

    bool Test::failedHierarchy() const
    {
        if (failed())
            return true;
        return std::any_of(m_Tests.begin(), m_Tests.end(), [](auto& t)
        {
            return t->failedHierarchy();
        });
    }

    const std::vector<Error>& Test::errors() const
    {
        return m_Errors;
    }

    void Test::addError(const Error& error)
    {
        m_Errors.push_back(error);
    }

    void Test::addError(Error&& error)
    {
        m_Errors.push_back(std::move(error));
    }

    size_t Test::depth() const
    {
        size_t d = 0;
        for (const auto& test : m_Tests)
            d = std::max(d, test->depth());
        return d + 1;
    }

    const std::string& Test::name() const
    {
        return m_Name;
    }

    clock_t Test::startTime() const
    {
        return m_StartTime;
    }

    void Test::setStartTime(clock_t startTime)
    {
        m_StartTime = startTime;
    }

    clock_t Test::endTime() const
    {
        return m_EndTime;
    }

    void Test::setEndTime(clock_t endTime)
    {
        m_EndTime = endTime;
    }

    double Test::elapsedTime() const
    {
        return static_cast<double>(m_EndTime - m_StartTime) / CLOCKS_PER_SEC;
    }

    void Test::addTest(const TestPtr& test)
    {
        m_Tests.push_back(test);
    }

    std::vector<TestPtr>& Test::tests()
    {
        return m_Tests;
    }

    const std::vector<TestPtr>& Test::tests() const
    {
        return m_Tests;
    }

    TestPtr Test::findTest(const std::string& name) const
    {
        auto it = std::find_if(
                begin(m_Tests), end(m_Tests),
                [&](const TestPtr& t){return t->name() == name;});
        if (it != end(m_Tests))
            return *it;
        else
            return {};
    }
}
