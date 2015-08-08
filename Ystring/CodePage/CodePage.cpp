//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePage.hpp"
#include <stdexcept>
#include <vector>
#include "../YstringException.hpp"
#include "../Utilities/KeyFunctionAlgorithms.hpp"
#include "Cp437.hpp"
#include "Iso8859_1.hpp"
#include "Windows1252.hpp"

namespace Ystring { namespace CodePage {

CodePage::CodePage(const uint32_t* toCodePoints,
                   const CodePointMapping* firstFromCodePoints,
                   const CodePointMapping* lastFromCodePoints,
                   Encoding_t encoding)
    : m_ToCodePoints(toCodePoints),
      m_FirstFromCodePoints(firstFromCodePoints),
      m_LastFromCodePoints(lastFromCodePoints),
      m_Encoding(encoding)
{}

uint32_t CodePage::toCodePoint(char c) const
{
    return m_ToCodePoints[static_cast<uint8_t>(c)];
}

uint32_t CodePage::fromCodePoint(uint32_t c) const
{
    if (c < 256 && m_ToCodePoints[c] == c)
        return c;
    auto it = Utilities::binaryFind(
        m_FirstFromCodePoints, m_LastFromCodePoints, c,
        [](const std::pair<uint32_t, char>& p){return p.first;});
    if (it != m_LastFromCodePoints)
        return it->second;
    return INVALID_CHAR;
}

Encoding_t CodePage::encoding() const
{
    return m_Encoding;
}

CodePage makeCodePage(Encoding_t encoding)
{
    switch (encoding)
    {
    case Encoding::ISO_8859_1:
        return makeIso8859_1();
    case Encoding::WINDOWS_1252:
        return makeWindows1252();
    case Encoding::CP_437:
        return makeCp437();
    default:
        break;
    }
    YSTRING_THROW("Unsupported code page encoding.");
}

}}
