//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-12.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "Macros.hpp"

int main(int argc, char* argv[])
{
    using namespace Ytest;
    try
    {
        if (!Session::instance().parseCommandLine(argc, argv))
            return 1;
        Y_CONSOLE_BEGIN();
        AutoTestRunner::instance().run();
        Y_CONSOLE_END();
    }
    catch (std::exception& ex)
    {
        std::cerr << "EXCEPTION: " << ex.what() << std::endl;
        return 1;
    }
    return (int)Session::instance().numberOfFailedTests();
}
