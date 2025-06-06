//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-06.
//
// This file is distributed under the Zero-Clause BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iosfwd>

namespace Ytest
{
    class Session;

    bool isRunningInVisualStudio();

    void writeVisualStudioReport(
            void (*reportFunc)(std::ostream&, const Session&),
            const Session& session);
}
