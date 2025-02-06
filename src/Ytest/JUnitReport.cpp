//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "JUnitReport.hpp"

#include <iomanip>
#include "Ytest/Session.hpp"
#include "Test.hpp"
#include "XmlWriter.hpp"

namespace Ytest
{
    void addTestCases(std::map<std::string, std::vector<TestPtr>>& testCases,
                      std::string path, const TestPtr& test)
    {
        if (test->assertions() > 0)
            testCases[path].push_back(test);
        auto subtests = test->tests();
        if (!subtests.empty())
        {
            if (!path.empty())
                path += "/";
            path += test->name();
            for (auto& subtest : subtests)
                addTestCases(testCases, path, subtest);
        }
    }

    std::map<std::string, std::vector<TestPtr>> getTestCases(
            const std::vector<TestPtr>& tests)
    {
        std::map<std::string, std::vector<TestPtr>> testCases;
        for (const auto& test : tests)
            addTestCases(testCases, std::string(), test);
        return testCases;
    }

     void writeXmlError(XmlWriter& writer, const Error& error)
     {
         if (error.type() == Error::UnhandledException)
             writer.beginElement("error");
         else
             writer.beginElement("failure");
         writer.attribute("message", error.message());
         writer.attribute("type", Error::levelName(error.type()));
         writer.characterData(error.file());
         writer.characterData("[");
         writer.characterData(static_cast<int>(error.lineNo()));
         writer.characterData("]");
         auto& context = error.context();
         for (const auto& c : context)
         {
             writer.characterData("\n");
             writer.characterData(c.text());
         }
         writer.endElement();
     }

     void writeXmlTestCase(XmlWriter& writer, const Test& test)
     {
         writer.beginElement("testcase");
         writer.attribute("name", test.name());
         writer.attribute("classname", std::string_view());
         if (test.assertions() != 0)
         {
             writer.attribute("assertions", static_cast<int64_t>(test.assertions()));
             writer.attribute("time", test.elapsedTime());
             auto& errors = test.errors();
             for (const auto& error : errors)
                 writeXmlError(writer, error);
         }
         writer.endElement();
     }

    void writeJUnitReport(std::ostream& os, const Session& session)
    {
         auto suites = getTestCases(session.tests());
         XmlWriter writer(os);
         writer.setFormatting(XmlWriter::IndentElements);
         writer.beginElement("testsuites");
         for (auto& [name, tests] : suites)
         {
             writer.beginElement("testsuite");
             writer.attribute("name", name);
             writer.attribute("tests", static_cast<int64_t>(tests.size()));
             for (const auto& test : tests)
             {
                 writeXmlTestCase(writer, *test);
             }
             writer.endElement();
         }
         writer.endElement();
    }
}
