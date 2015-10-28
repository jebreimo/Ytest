//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#ifdef _WIN32
    #pragma comment (lib, "Ytest.lib")
#endif

#include "Ytest/AutoTest.hpp"
#include "Ytest/AutoTestRunner.hpp"
#include "Ytest/Macros.hpp"
#include "Ytest/Session.hpp"

#ifdef Y_MAIN

#include "Ytest/YtestMain.hpp"

#endif
