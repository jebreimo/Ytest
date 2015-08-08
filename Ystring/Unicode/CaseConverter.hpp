//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-07-01
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <functional>
#include "CharMap.hpp"

namespace Ystring { namespace Unicode {

uint32_t lower(uint32_t ch);
uint32_t title(uint32_t ch);
uint32_t upper(uint32_t ch);

}}
