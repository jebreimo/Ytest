/* JEBTest: A C++ unit testing framework
 * Copyright 2013 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "../../Ytest.hpp"
#include <stdexcept>
#include <vector>

static double divide(double a, double b)
{
    if (b == 0)
        throw std::invalid_argument("division by zero");
    return a / b;
}

// static void throwsSuccessful()
// {
//     Y_THROWS(divide(1, 0), std::logic_error);
// }

// static void throwsUnsuccessful()
// {
//     Y_THROWS(divide(5, 2.5), std::logic_error);
// }

static void testEXPECT()
{
    std::vector<int> foo(2);
    Y_EXPECT(foo.empty());
    Y_EXPECT(!foo.empty());
    Y_EXPECT(foo.size() == 4);
    Y_EXPECT(foo.size() == 2);
}

static void testEXPECT_MSG()
{
    std::vector<int> foo(2);
    Y_EXPECT_MSG(foo.empty(), "Vector isn't empty!");
    Y_EXPECT_MSG(!foo.empty(), "Vector is empty!");
    Y_EXPECT_MSG(foo.size() == 3, "Size isn't 3!");
    Y_EXPECT_MSG(foo.size() == 2, "Size is 2!");
}

static void testEQUAL()
{
    Y_EQUAL(divide(10, 3), 3.333);
    Y_EQUAL(divide(10, 2), 5);
}

// static void equivalentSuccessful()
// {
//     Y_EQUIVALENT(divide(10, 3), 3.333, 0.001);
// }

// static void equivalentUnsuccessful()
// {
//     Y_EQUIVALENT(divide(10, 3), 3.333, 0.0001);
// }

// static void notEqualSuccessful()
// {
//     Y_NOT_EQUAL(divide(10, 2), 4.999);
// }

// static void notEqualUnsuccessful()
// {
//     Y_NOT_EQUAL(divide(10, 2), 5);
// }

Y_SUBTEST("BasicMacroTests",
           testEXPECT,
           testEXPECT_MSG,
           testEQUAL);
