//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include "AutoTest.hpp"
#include "Comparers.hpp"
#include "Exceptions.hpp"
#include "Formatters.hpp"
#include "MacroUtilities.hpp"
#include "Session.hpp"
#include "TestScope.hpp"

/** @file
  *  @brief Defines all macros for tests, test suites and test setup.
  *
  *  The macros in this file fall in following categories:
  *  - macros for defining the main function and executing all test suites
  *  - macros for defining test suites and adding and executing tests
  *  - macros for doing the actual testing, e.g. JT_ASSERT and JT_EQUAL
  */

/** @brief Internal macro. Used by other macros to create unique
  *     variable names.
  */
#define JT_PRIV_UNIQUE_NAME_EXPANDER2(a, b) a##b

/** @brief Internal macro. Used by other macros to create unique
  *     variable names.
  */
#define JT_PRIV_UNIQUE_NAME_EXPANDER1(a, b) JT_PRIV_UNIQUE_NAME_EXPANDER2(a, b)

/** @brief Internal macro. Used by other macros to create unique
  *     variable names.
  */
#define JT_PRIV_UNIQUE_NAME(name) JT_PRIV_UNIQUE_NAME_EXPANDER1(name, __LINE__)

/** @brief Starts a scope for running tests and test suites.
  *
  * All reports and messages are written to the console (command
  * line window).
  */
#define JT_CONSOLE_BEGIN() \
    try {

/** @brief Ends a scope for running tests and test suites.
  *
  * All reports and messages are written to the console (command
  * line window).
  */
#define JT_CONSOLE_END() \
    } catch (...) {} \
    ::Ytest::Session::instance().print(""); \
    ::Ytest::Session::instance().flushLog(); \
    ::Ytest::Session::instance().writeReports()

/** @brief Creates a main function for console programs that run test suites.
  *
  * The created main function will run all tests in all test suites defined
  * with the JT_TESTSUITE macro or added explicitly with a AutoTest variable.
  *
  * All reports and messages are written to the console (command line window)
  */
#define JT_CONSOLE_MAIN() \
    int main(int argc, char* argv[]) \
    { \
        try { \
            if (!::Ytest::Session::instance().parseCommandLine(argc, argv)) \
                return 1; \
            JT_CONSOLE_BEGIN(); \
            ::Ytest::AutoTestRunner::instance().run(); \
            JT_CONSOLE_END(); \
        } catch (std::exception& ex) { \
            std::cerr << "EXCEPTION: " << ex.what() << std::endl; \
            return 1; \
        } \
        return (int)::Ytest::Session::instance().numberOfFailedTests(); \
    }

/** @brief Defines a test suite.
  *
  * The arguments to this macro are the function names of the test functions.
  * The test functions are executed in the order they are given.
  * There are no restrictions to how many functions that can be added.
  *
  * The test suite's name in reports will be the current file name.
  */
#define JT_TEST(...) \
    static void JT_PRIV_UNIQUE_NAME(JT_suite_)() \
    { \
        std::function<void()> tests_JT_[] = {__VA_ARGS__}; \
        ::Ytest::runTests(__FILE__, __LINE__, #__VA_ARGS__, tests_JT_); \
    } \
    static ::Ytest::AutoTest JT_PRIV_UNIQUE_NAME(JT_suite_instance_) \
            (__FILE__, JT_PRIV_UNIQUE_NAME(JT_suite_))

#define JT_SUBTEST(path, ...) \
    static void JT_PRIV_UNIQUE_NAME(JT_suite_)() \
    { \
        std::function<void()> tests_JT_[] = {__VA_ARGS__}; \
        ::Ytest::runTests(__FILE__, __LINE__, #__VA_ARGS__, tests_JT_); \
    } \
    static ::Ytest::AutoTest JT_PRIV_UNIQUE_NAME(JT_suite_instance_) \
            (__FILE__, JT_PRIV_UNIQUE_NAME(JT_suite_), (path))

#define JT_PRIORITIZED_TEST(priority, ...) \
    static void JT_PRIV_UNIQUE_NAME(JT_suite_)() \
    { \
        std::function<void()> tests_JT_[] = {__VA_ARGS__}; \
        ::Ytest::runTests(__FILE__, __LINE__, #__VA_ARGS__, tests_JT_); \
    } \
    static ::Ytest::AutoTest JT_PRIV_UNIQUE_NAME(JT_suite_instance_) \
            (__FILE__, JT_PRIV_UNIQUE_NAME(JT_suite_), "", (priority))

#define JT_PRIORITIZED_SUBTEST(priority, path, ...) \
    static void JT_PRIV_UNIQUE_NAME(JT_suite_)() \
    { \
        std::function<void()> tests_JT_[] = {__VA_ARGS__}; \
        ::Ytest::runTests(__FILE__, __LINE__, #__VA_ARGS__, tests_JT_); \
    } \
    static ::Ytest::AutoTest JT_PRIV_UNIQUE_NAME(JT_suite_instance_) \
            (__FILE__, JT_PRIV_UNIQUE_NAME(JT_suite_), (path), (priority))

/** @brief Macro for explcitly running a test with arguments.
  *
  * Normally you'll just use JT_TEST to define your tests, but
  * if your tests need a common set of data, for instance the contents of a
  * file, it may make sense to create a "test suite function" that reads the
  * file first, then run each test function with the contents of that file
  * as input arguments. This function simplifies executing such a function.
  *
  * @param name the name of the test function
  * @param ... comma separated arguments that will be passed on to @a name.
  *
  * Examples
  * --------
  * Execute a test function named test_Shapes that takes no
  * arguments:
  *
  *     void test_Shapes() {...}
  *
  *     JT_RUN_TEST(test_Shapes);
  *
  * Execute a test function named test_SvgShapes that takes a file
  * name as argument:
  *
  *     void test_SvgShapes(std::string fileName) {...}
  *
  *     void test_SvgTests()
  *     {
  *         JT_RUN_TEST(test_SvgShapes, "first_svg_file.svg");
  *         JT_RUN_TEST(test_SvgShapes, "second_svg_file.svg");
  *     }
  */
#define JT_RUN_TEST(name, ...) \
    if (::Ytest::Session::instance().isTestEnabled(#name)) \
    { \
        ::Ytest::TestScope scope(#name); \
        try { \
            name(__VA_ARGS__); \
        } catch (const ::Ytest::AbstractFailure& ex) { \
            ::Ytest::Session::instance().testFailed(ex.error()); \
            if (ex.error().type() != ::Ytest::Error::Failure) \
                throw; \
        } catch (const std::exception& ex) { \
            ::Ytest::Session::instance().testFailed(::Ytest::Error( \
                    __FILE__, __LINE__, \
                    std::string("Unhandled exception: \"") + ex.what() \
                    + "\"", ::Ytest::Error::UnhandledException)); \
            throw; \
        } catch (...) { \
            ::Ytest::Session::instance().testFailed(::Ytest::Error( \
                    __FILE__, __LINE__, \
                    "Unhandled exception (not derived from std::exception)", \
                    ::Ytest::Error::UnhandledException)); \
            throw; \
        } \
    }

#define JT_IMPL_THROWS(expr, exception, failure, file, line, msg) \
    do { \
        try { \
            expr; \
            throw ::Ytest::failure(file, line, msg); \
        } catch (const exception&) { \
            ::Ytest::Session::instance().assertPassed(); \
        } \
    } while (false)

/** @brief Macro for verifying that an expression throws an exception.
  *
  * The test fails if @a expr doesn't throw an exception of type @a exception.
  *
  * @param expr the expression that will be executed, typically
  *     a function call
  * @param exception the type name of the exception that @a expr is expected
  *     to throw
  */
#define JT_THROWS(expr, exception) \
    JT_IMPL_THROWS(expr, exception, TestFailure, __FILE__, __LINE__, \
                   #expr " didn't throw exception \"" #exception "\"")

#define JT_THROWS_CRITICAL(expr, exception) \
    JT_IMPL_THROWS(expr, exception, CriticalFailure, __FILE__, __LINE__, \
                   #expr " didn't throw exception \"" #exception "\"")

#define JT_THROWS_FATAL(expr, exception) \
    JT_IMPL_THROWS(expr, exception, FatalFailure, __FILE__, __LINE__, \
                   #expr " didn't throw exception \"" #exception "\"")

#define JT_IMPL_EXPECT(cond, file, line, msg) \
    do { \
        if (cond) { \
            ::Ytest::Session::instance().assertPassed(); \
        } else { \
            ::Ytest::Session::instance().testFailed(::Ytest::Error( \
                    file, line, msg, ::Ytest::Error::Failure)); \
        } \
    } while (false)

#define JT_EXPECT(cond) \
    JT_IMPL_EXPECT((cond), __FILE__, __LINE__, "Assertion failed: " #cond)

#define JT_EXPECT_EQUAL(a, b) \
    JT_IMPL_EXPECT(::Ytest::equal((a), (b)), \
                   __FILE__, __LINE__, \
                   ::Ytest::formatComparison((a), #a, (b), #b, "!="))

#define JT_EXPECT_MSG(cond, msg) \
    do { \
        if (cond) { \
            ::Ytest::Session::instance().assertPassed(); \
        } else { \
            std::ostringstream JT_os; \
            JT_os << "Error: " #cond ". " << msg; \
            ::Ytest::Session::instance().testFailed(::Ytest::Error( \
                    __FILE__, __LINE__, JT_os.str(), \
                    ::Ytest::Error::Failure)); \
        } \
    } while (false)


/** @brief Internal macro. Used by other assert macros.
  */
#define JT_IMPL_ASSERT(cond, failure, file, line, msg) \
    do { \
        if (cond) { \
            ::Ytest::Session::instance().assertPassed(); \
        } else { \
            throw ::Ytest::failure(file, line, msg); \
        } \
    } while (false)

/** @brief Verifies that condition @a cond is true.
  *
  * The test fails if @a cond is false.
  */
#define JT_ASSERT(cond) \
    JT_IMPL_ASSERT((cond), TestFailure, __FILE__, __LINE__, \
                   "Assertion failed: " #cond)

#define JT_ASSERT_CRITICAL(cond) \
    JT_IMPL_ASSERT((cond), CriticalFailure, __FILE__, __LINE__, \
                   "Assertion failed: " #cond)

#define JT_ASSERT_FATAL(cond) \
    JT_IMPL_ASSERT((cond), FatalFailure, __FILE__, __LINE__, \
                   "Assertion failed: " #cond)

#define JT_IMPL_ASSERT_MSG(cond, condStr, failure, file, line, msg) \
    do { \
        if (cond) { \
            ::Ytest::Session::instance().assertPassed(); \
        } else { \
            std::ostringstream JT_os; \
            JT_os << "Assertion failed: " condStr ". " << msg; \
            throw ::Ytest::failure(file, line, JT_os.str()); \
        } \
    } while (false)

/** @brief Verifies that condition @a cond is true.
  *
  * Use this macro to provide extra information about the condition if it
  * fails.
  *
  * @param cond the condition
  * @param msg a string that that will be include in the test report if
  *     @a cond is false.
  */
#define JT_ASSERT_MSG(cond, msg) \
    JT_IMPL_ASSERT_MSG(cond, #cond, TestFailure, __FILE__, __LINE__, msg)

#define JT_ASSERT_MSG_CRITICAL(cond, msg) \
    JT_IMPL_ASSERT_MSG(cond, #cond, CriticalFailure, __FILE__, __LINE__, msg)

#define JT_ASSERT_MSG_FATAL(cond, msg) \
    JT_IMPL_ASSERT_MSG(cond, #cond, FatalFailure, __FILE__, __LINE__, msg)

#define JT_IMPL_COMPARISON(test, a, b, failure, file, line, cmpStr) \
    do { \
        auto&& JT_PRIV_UNIQUE_NAME(aa) = (a); \
        auto&& JT_PRIV_UNIQUE_NAME(bb) = (b); \
        JT_IMPL_ASSERT( \
                test(JT_PRIV_UNIQUE_NAME(aa), JT_PRIV_UNIQUE_NAME(bb)), \
                failure, file, line, \
                ::Ytest::formatComparison(JT_PRIV_UNIQUE_NAME(aa), #a, \
                                            JT_PRIV_UNIQUE_NAME(bb), #b, \
                                            cmpStr)); \
    } while (false)

#define JT_IMPL_EQUIVALENT(a, b, epsilon, failure, file, line) \
    do { \
        auto&& JT_PRIV_UNIQUE_NAME(aa) = (a); \
        auto&& JT_PRIV_UNIQUE_NAME(bb) = (b); \
        JT_IMPL_ASSERT( \
                ::Ytest::equivalent(JT_PRIV_UNIQUE_NAME(aa), \
                                      JT_PRIV_UNIQUE_NAME(bb), epsilon), \
                failure, file, line, \
                ::Ytest::formatComparison(JT_PRIV_UNIQUE_NAME(aa), #a, \
                                            JT_PRIV_UNIQUE_NAME(bb), #b, \
                                            "!=")); \
    } while (false)

/** @brief Verifies that @a a equals @a b.
  *
  * Requirements for a and b:
  * - there must be an equality operator (==) that accepts @a a and @a b as
  *   left and right hand arguments respectively.
  * - there must be an iostream output operator (<<) that accepts @a a.
  * - if @a b is not of the same type as @a a, there must also be an iostream
  *   output operator that accepts @a b.
  */
#define JT_EQUAL(a, b) \
    JT_IMPL_COMPARISON(::Ytest::equal, a, b, TestFailure, \
                       __FILE__, __LINE__, "!=")

#define JT_EQUAL_CRITICAL(a, b) \
    JT_IMPL_COMPARISON(::Ytest::equal, a, b, CriticalFailure, \
                       __FILE__, __LINE__, "!=")

#define JT_EQUAL_FATAL(a, b) \
    JT_IMPL_COMPARISON(::Ytest::equal, a, b, FatalFailure, \
                       __FILE__, __LINE__, "!=")

#define JT_GREATER(a, b) \
    JT_IMPL_COMPARISON(::Ytest::greaterThan, a, b, TestFailure, \
                       __FILE__, __LINE__, "<=")

#define JT_LESS(a, b) \
    JT_IMPL_COMPARISON(::Ytest::lessThan, a, b, TestFailure, \
                       __FILE__, __LINE__, ">=")

#define JT_EQUAL_RANGES(a, b) \
    do { \
        auto resultYtest = ::Ytest::equalRanges(a, b, #a, #b); \
        JT_IMPL_ASSERT(resultYtest.first, TestFailure, __FILE__, __LINE__, \
                       resultYtest.second); \
    } while (false)

/** @brief Verifies that number @a a is sufficiently close to @a b.
  */
#define JT_EQUIVALENT(a, b, epsilon) \
    JT_IMPL_EQUIVALENT(a, b, epsilon, TestFailure, __FILE__, __LINE__)

#define JT_EQUIVALENT_CRITICAL(a, b, epsilon) \
    JT_IMPL_EQUIVALENT(a, b, epsilon, CriticalFailure, __FILE__, __LINE__)

#define JT_EQUIVALENT_FATAL(a, b, epsilon) \
    JT_IMPL_EQUIVALENT(a, b, epsilon, FatalFailure, __FILE__, __LINE__)

/** @brief Verifies that @a a is not equal to @a b.
  *
  *  Requirements to @a a and @a b are the same as in JT_EQUAL.
  */
#define JT_NOT_EQUAL(a, b) \
    JT_IMPL_COMPARISON(::Ytest::notEqual, a, b, TestFailure, \
                       __FILE__, __LINE__, "==")

#define JT_NOT_EQUAL_CRITICAL(a, b) \
    JT_IMPL_COMPARISON(::Ytest::notEqual, a, b, CriticalFailure, \
                       __FILE__, __LINE__, "==")

#define JT_NOT_EQUAL_FATAL(a, b) \
    JT_IMPL_COMPARISON(::Ytest::notEqual, a, b, FatalFailure, \
                       __FILE__, __LINE__, "==")

/** @brief Force a test failure with the given error message.
  */
#define JT_FAILURE(msg) \
    throw ::Ytest::TestFailure(__FILE__, __LINE__, msg)

#define JT_CRITICAL_FAILURE(msg) \
    throw ::Ytest::CriticalFailure(__FILE__, __LINE__, msg)

#define JT_FATAL_FAILURE(msg) \
    throw ::Ytest::FatalFailure(__FILE__, __LINE__, msg)

/** @brief Provide extra call-stack information when calling a function from
  *     within a test function.
  *
  *  If a test function calls another function that uses JT-macros to test
  *  various conditions, surround the calls to the other function with this
  *  macro to include call stack information in the test report.
  *
  *  To reduce code duplication it often makes sense to place the different
  *  assert macros in a function that is called from the actual test function.
  *  The test report will in such cases only contain the line number of the
  *  assert that failed, which may not provide much information about the
  *  condition that made the fail test if this assertion is executed many
  *  times. This macro helps solve that problem.
  */
#define JT_CALL(expr) \
    do { \
        try \
        { \
            expr; \
        } \
        catch (::Ytest::TestFailure& ex) \
        { \
            ex.addContext(__FILE__, __LINE__, #expr); \
            throw ex; \
        } \
    } while (false)

#define JT_CALL_1(expr, arg1) \
    do { \
        try \
        { \
            expr; \
        } \
        catch (::Ytest::TestFailure& ex) \
        { \
            std::stringstream ss; \
            ss << #expr " // " #arg1 "=" << arg1; \
            ex.addContext(__FILE__, __LINE__, ss.str()); \
            throw ex; \
        } \
    } while (false)


#define JT_CALL_2(expr, arg1, arg2) \
    do { \
        try \
        { \
            expr; \
        } \
        catch (::Ytest::TestFailure& ex) \
        { \
            std::stringstream ss; \
            ss << #expr " // " #arg1 "=" << arg1 << ", " #arg2 "=" << arg2; \
            ex.addContext(__FILE__, __LINE__, ss.str()); \
            throw ex; \
        } \
    } while (false)
