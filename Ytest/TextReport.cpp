//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "TextReport.hpp"

#include <ostream>
#undef JEB

#include "Session.hpp"
#include "Test.hpp"

namespace Ytest {

struct Counters
{
    Counters() : assertions(), tests(), failedTests(), errors() {}
    size_t assertions;
    size_t tests;
    size_t failedTests;
    size_t errors;
};

Counters& operator+=(Counters& lhs, const Counters& rhs)
{
    lhs.assertions += rhs.assertions;
    lhs.tests += rhs.tests;
    lhs.failedTests += rhs.failedTests;
    return lhs;
}

static std::string testName(const std::vector<TestPtr>& parents,
                            const TestPtr& test)
{
    std::string name;
    for (auto it = parents.begin(); it != parents.end(); ++it)
        name += (*it)->name() + "/";
    name += test->name();
    return name;
}

static Counters writeTextReport(
        std::ostream& os,
        const std::vector<TestPtr>& tests,
        std::vector<TestPtr>& parents)
{
    Counters counters;
    for (auto it = tests.begin(); it != tests.end(); ++it)
    {
        if ((*it)->failed() || (*it)->tests().empty() || (*it)->assertions())
            ++counters.tests;
        counters.assertions += (*it)->assertions();
        if (!(*it)->tests().empty())
        {
            parents.push_back(*it);
            counters += writeTextReport(os, (*it)->tests(), parents);
            parents.pop_back();
        }
        auto& errors = (*it)->errors();
        if ((*it)->failed())
        {
            ++counters.failedTests;
            os << testName(parents, *it) << ": FAILED (assertion "
               << ((*it)->assertions() + 1) << ")\n";
        }
        else if (!errors.empty())
        {
            os << testName(parents, *it) << ": SUCCEEDED WITH WARNINGS\n";
        }
        for (auto err = begin(errors); err != end(errors); ++err)
        {
            ++counters.errors;
            os << "    " << *err << "\n";
            const std::vector<Error>& context = err->context();
            if (!context.empty())
            {
                os << "    Called from:\n";
                for (auto c = context.begin(); c != context.end(); ++c)
                    os << "        " << c->text() << "\n";
            }
        }
    }
    return counters;
}

void writeTextReport(std::ostream& os, const Session& session)
{
    if (session.tests().empty())
    {
        os << "No tests were executed.\n";
        return;
    }
    os << "\n=== Test Report ===\n";
    std::vector<TestPtr> parents;
    Counters counters = writeTextReport(os, session.tests(), parents);
    os << counters.assertions << " assertions passed.\n"
       << (counters.tests - counters.failedTests) << " tests passed.\n"
       << counters.failedTests << " tests failed.\n";
    if (counters.failedTests)
        os << "=== TESTS FAILED ===\n";
    else
        os << "=== TESTS PASSED ===\n";
    os.flush();
}

}
