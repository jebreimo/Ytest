//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-2115
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include "../Encoding.hpp"

/** @namespace CodePage
  * @brief The namespace for everything specific to single byte
  *     character sets.
  */
namespace Ystring { namespace CodePage {

typedef std::pair<uint32_t, uint8_t> CodePointMapping;

class CodePage
{
public:
    CodePage(const uint32_t* toCodePoints,
             const CodePointMapping* firstFromCodePoints,
             const CodePointMapping* lastFromCodePoints,
             Encoding_t encoding);

    uint32_t toCodePoint(char c) const;
    uint32_t fromCodePoint(uint32_t c) const;
    Encoding_t encoding() const;
private:
    const uint32_t* m_ToCodePoints;
    const CodePointMapping* m_FirstFromCodePoints;
    const CodePointMapping* m_LastFromCodePoints;
    Encoding_t m_Encoding;
};

CodePage makeCodePage(Encoding_t encoding);

}}
