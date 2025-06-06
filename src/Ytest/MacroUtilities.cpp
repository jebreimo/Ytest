//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ytest/MacroUtilities.hpp"

#include <cassert>
#include "Ystring/Algorithms.hpp"
#include "Ytest/Exceptions.hpp"
#include "Ytest/Session.hpp"
#include "Ytest/TestScope.hpp"

namespace Ytest
{
    namespace
    {
        std::vector<std::string> extractTestNames(const std::string& names)
        {
            std::vector<std::string> result;
            for (auto & it : ystring::split(names, ","))
              result.emplace_back(ystring::trim(it));
            return result;
        }
    }

    void runTests(const char* file, int line, const char* testNamesString,
                  std::function<void()>* testFuncs, size_t testFuncsSize)
    {
        auto testNames = extractTestNames(testNamesString);
        assert(testNames.size() == testFuncsSize);
        for (size_t i = 0; i < testNames.size(); i++)
        {
            if (!Session::instance().isTestEnabled(testNames[i]))
                continue;

            TestScope scope(testNames[i]);
            try
            {
                testFuncs[i]();
            }
            catch (const Failure& ex)
            {
                Session::instance().testFailed(ex.error());
                if (ex.error().type() != Error::Failure)
                    throw;
            }
            catch (const std::exception& ex)
            {
                Session::instance().testFailed(Error(file, line,
                    std::string("Unhandled exception: \"") + ex.what() + "\"",
                                Error::UnhandledException));
                throw;
            }
            catch (...)
            {
                Session::instance().testFailed(Error(file, line,
                    "Unhandled exception (not derived from std::exception)",
                    Error::UnhandledException));
                throw;
            }
        }
    }
}
