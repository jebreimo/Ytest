//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ytest/AutoTestRunner.hpp"

#include <algorithm>
#include "Ytest/AutoTest.hpp"
#include "Ytest/Exceptions.hpp"
#include "Ytest/Session.hpp"
#include "Ytest/TestScope.hpp"

namespace Ytest
{
    AutoTestRunner::AutoTestRunner() = default;

    AutoTestRunner& AutoTestRunner::instance()
    {
        static AutoTestRunner runner;
        return runner;
    }

    void AutoTestRunner::addTest(const AutoTest* suite)
    {
        m_Tests.push_back(suite);
    }

    static bool hasHigherPriority(const AutoTest* a, const AutoTest* b)
    {
        if (a->priority() >= 0 && b->priority() >= 0)
            return a->priority() < b->priority();
        else
            return a->priority() > b->priority();
    }

    void AutoTestRunner::run()
    {
        std::sort(m_Tests.begin(), m_Tests.end(), hasHigherPriority);
        for (auto & m_Test : m_Tests)
        {
            TestScope scope;
            auto& session = Session::instance();
            auto& path = m_Test->path();
            auto name = begin(path);
            for (; name != end(path); ++name)
            {
                if (session.isTestEnabled(*name))
                    scope.push(*name, true);
            }
            if (name == end(path) && session.isTestEnabled(m_Test->name()))
            {
                scope.push(m_Test->name());
                try
                {
                    m_Test->function()();
                }
                catch (const TestFailure&)
                {}
                catch (const CriticalFailure&)
                {}
            }
        }
    }
}
