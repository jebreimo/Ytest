//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "AutoTest.hpp"

#include <limits>
#include "../Ystring/Predicates.hpp"
#include "../Ystring/Utf8.hpp"
// #include "JEBIO/JEBPath.hpp"
#include "AutoTestRunner.hpp"
#include "MacroUtilities.hpp"

namespace Ytest {

using namespace Ystring;
// using namespace Ytest_Yio;

namespace
{
    std::string extractSuiteName(const std::string& path)
    {
        auto parts = Utf8::splitIf(path, isPathSeparator, -1,
                                   SplitFlags::IGNORE_REMAINDER);
        auto parts2 = Utf8::split(parts[0], ".", -1);
        return parts2.back();
    }
}

AutoTest::AutoTest(const std::string& fileName, Func func,
                   const std::string& path)
    : m_Function(func),
      m_Name(fileName),
      m_Priority(std::numeric_limits<int>::max())
{
    if (!path.empty())
        m_Path = Utf8::split(path, "/");
    AutoTestRunner::instance().addTest(this);
}

AutoTest::AutoTest(const std::string& fileName, Func func,
                   const std::string& path, int priority)
    : m_Function(func),
      m_Name(fileName),
      m_Priority(priority)
{
    if (!path.empty())
        m_Path = Utf8::split(path, "/");
    AutoTestRunner::instance().addTest(this);
}

AutoTest::~AutoTest()
{}

const AutoTest::Func& AutoTest::function() const
{
    return m_Function;
}

void AutoTest::setFunction(const Func& function)
{
    m_Function = function;
}

std::string AutoTest::name() const
{
    return extractSuiteName(m_Name);
}

const std::vector<std::string>& AutoTest::path() const
{
    return m_Path;
}

int AutoTest::priority() const
{
    return m_Priority;
}

}
