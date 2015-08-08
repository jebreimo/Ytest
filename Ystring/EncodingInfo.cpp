//****************************************************************************
// Copyright © 2014 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2014-03-15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "EncodingInfo.hpp"

#include <functional>
#include <istream>
#include "Utf8/DecodeUtf8.hpp"
#include "Utf8.hpp"

namespace Ystring {

EncodingInfo::EncodingInfo()
    : m_Endianness(Utilities::UnknownEndianness),
      m_MinCharLength(0),
      m_MaxCharLength(0),
      m_Encoding(Encoding::UNKNOWN),
      m_UnitSize(0)
{
}

EncodingInfo::EncodingInfo(Encoding_t encoding,
                           const std::string& name,
                           const std::string& byteOrderMark,
                           Utilities::Endianness endianness,
                           size_t unitSize,
                           size_t minCharLength,
                           size_t maxCharLength)
    : m_ByteOrderMark(byteOrderMark),
      m_Endianness(endianness),
      m_MinCharLength(minCharLength),
      m_MaxCharLength(maxCharLength),
      m_Name(name),
      m_Encoding(encoding),
      m_UnitSize(unitSize)
{
}

const std::string& EncodingInfo::byteOrderMark() const
{
    return m_ByteOrderMark;
}

void EncodingInfo::setByteOrderMark(const std::string& byteOrderMark)
{
    m_ByteOrderMark = byteOrderMark;
}

Utilities::Endianness EncodingInfo::endianness() const
{
    return m_Endianness;
}

void EncodingInfo::setEndianness(Utilities::Endianness endianness)
{
    m_Endianness = endianness;
}

size_t EncodingInfo::minCharLength() const
{
    return m_MinCharLength;
}

void EncodingInfo::setMinCharLength(size_t minCharLength)
{
    m_MinCharLength = minCharLength;
}

size_t EncodingInfo::maxCharLength() const
{
    return m_MaxCharLength;
}

void EncodingInfo::setMaxCharLength(size_t maxCharLength)
{
    m_MaxCharLength = maxCharLength;
}

const std::string& EncodingInfo::name() const
{
    return m_Name;
}

void EncodingInfo::setName(const std::string& name)
{
    m_Name = name;
}

Encoding_t EncodingInfo::encoding() const
{
    return m_Encoding;
}

void EncodingInfo::setEncoding(Encoding_t encoding)
{
    m_Encoding = encoding;
}

size_t EncodingInfo::unitSize() const
{
    return m_UnitSize;
}

void EncodingInfo::setUnitSize(size_t unitSize)
{
    m_UnitSize = unitSize;
}

typedef std::pair<std::string, Encoding_t> EncodingName;

static EncodingName s_EncodingMap[] = {
    EncodingName("ascii", Encoding::ASCII),
    EncodingName("us-ascii", Encoding::ASCII),
    EncodingName("utf8", Encoding::UTF_8),
    EncodingName("utf-8", Encoding::UTF_8),
    EncodingName("latin1", Encoding::LATIN_1),
    EncodingName("latin-1", Encoding::LATIN_1),
    EncodingName("iso8859-1", Encoding::LATIN_1),
    EncodingName("iso-8859-1", Encoding::LATIN_1),
    EncodingName("windows1252", Encoding::WINDOWS_1252),
    EncodingName("windows-1252", Encoding::WINDOWS_1252),
    EncodingName("cp1252", Encoding::WINDOWS_1252),
    EncodingName("cp-1252", Encoding::WINDOWS_1252),
    EncodingName("utf16", Encoding::UTF_16),
    EncodingName("utf-16", Encoding::UTF_16),
    EncodingName("utf16le", Encoding::UTF_16_LE),
    EncodingName("utf-16le", Encoding::UTF_16_LE),
    EncodingName("utf16be", Encoding::UTF_16_BE),
    EncodingName("utf-16be", Encoding::UTF_16_BE),
    EncodingName("utf32", Encoding::UTF_32),
    EncodingName("utf-32", Encoding::UTF_32),
    EncodingName("utf32le", Encoding::UTF_32_LE),
    EncodingName("utf-32le", Encoding::UTF_32_LE),
    EncodingName("utf32be", Encoding::UTF_32_BE),
    EncodingName("utf-32be", Encoding::UTF_32_BE),
    EncodingName("ucs-2", Encoding::UCS_2)
};

static EncodingInfo s_Properties[] = {
    EncodingInfo(Encoding::UNKNOWN, "Unknown", "",
                       Utilities::UnknownEndianness, 0, 0, 0),
    EncodingInfo(Encoding::ASCII, "ASCII", "",
                       Utilities::UnknownEndianness, 1, 1, 1),
    EncodingInfo(Encoding::UTF_8, "UTF-8", "\xEF\xBB\xBF",
                       Utilities::UnknownEndianness, 1, 1, 4),
    EncodingInfo(Encoding::LATIN_1, "latin-1", "",
                       Utilities::UnknownEndianness, 1, 1, 1),
    EncodingInfo(Encoding::WINDOWS_1252, "windows-1252", "",
                       Utilities::UnknownEndianness, 1, 1, 1),
    EncodingInfo(Encoding::UTF_16_BE, "UTF-16BE", "\xFE\xFF",
                       Utilities::BigEndian, 2, 1, 2),
    EncodingInfo(Encoding::UTF_16_LE, "UTF-16LE", "\xFF\xFE",
                       Utilities::LittleEndian, 2, 1, 2),
    EncodingInfo(Encoding::UTF_32_BE, "UTF-32BE", "\x00\x00\xFE\xFF",
                       Utilities::BigEndian, 4, 1, 1),
    EncodingInfo(Encoding::UTF_32_LE, "UTF-32LE", "\xFF\xFE\x00\x00",
                       Utilities::LittleEndian, 4, 1, 1),
    EncodingInfo(Encoding::UTF_7, "UTF-7", "\x2B\x2F\x76",
                       Utilities::UnknownEndianness, 1, 1, 0),
    EncodingInfo(Encoding::UTF_1, "UTF-1", "\xF7\x64\x4C",
                       Utilities::UnknownEndianness, 1, 1, 5),
    EncodingInfo(Encoding::UTF_EBCDIC, "UTF-EBCDIC", "\xDD\x73\x66\x73",
                       Utilities::UnknownEndianness, 1, 1, 5),
    EncodingInfo(Encoding::SCSU, "SCSU", "\x0E\xFE\xFF",
                       Utilities::UnknownEndianness, 1, 1, 0),
    EncodingInfo(Encoding::BOCU_1, "BOCU-1", "\xFB\xEE\x28",
                       Utilities::UnknownEndianness, 1, 1, 0),
    EncodingInfo(Encoding::UCS_2, "UCS2", "",
                       Utilities::BigEndian, 2, 1, 1),
    EncodingInfo(Encoding::GB_18030, "GB18030", "\x84\x31\x95\x33",
                       Utilities::UnknownEndianness, 1, 1, 4)
};

const EncodingInfo* encodingInfo(Encoding_t encoding)
{
    if (Encoding::UNKNOWN <= encoding && encoding < Encoding::MAXIMUM)
        return &s_Properties[encoding];
    else
        return NULL;
}

Encoding_t encodingFromName(const std::string& name)
{
    for (EncodingName* it = std::begin(s_EncodingMap); it != std::end(s_EncodingMap); ++it)
    {
        if (Utf8::caseInsensitiveEqual(it->first, name))
            return it->second;
    }
    return Encoding::UNKNOWN;
}

Encoding_t encodingFromByteOrderMark(const std::string& str)
{
    for (size_t i = 0; i < sizeof(s_Properties) / sizeof(*s_Properties); i++)
    {
        const std::string& bom = s_Properties[i].byteOrderMark();
        if (!bom.empty() &&
            str.size() >= bom.size() &&
            std::equal(bom.begin(), bom.end(), str.begin()))
        {
            if (s_Properties[i].encoding() != Encoding::UTF_7 ||
                (str.size() >= 4 && (str[3] == '8' || str[3] == '9' ||
                                     str[3] == '+' || str[3] == '/')))

                return s_Properties[i].encoding();
        }
    }
    return Encoding::UNKNOWN;
}

Encoding_t encodingFromByteOrderMark(const char* str, size_t len)
{
    assert(str != NULL);
    assert(len > 0);
    return encodingFromByteOrderMark(std::string(str, std::min(len, (size_t)4)));
}

bool getBytePatterns(const char* str, size_t len,
                     size_t patternSize,
                     unsigned& anded, unsigned& ored)
{
    assert(patternSize < sizeof(unsigned) * 8);
    if (len < patternSize)
        return false;
    anded = ~0u;
    ored = 0;
    for (size_t i = 0; i + patternSize <= len; i += patternSize)
    {
        unsigned pattern = 0;
        for (size_t j = 0; j < patternSize; j++)
            pattern |= str[i + j] == 0 ? 0 : (unsigned)(1u << j);

        anded &= pattern;
        ored |= pattern;
    }
    return true;
}

Encoding_t encodingFromPattern(unsigned pattern, size_t patternSize)
{
    if (patternSize == 4)
    {
        switch (pattern)
        {
        case 0x1: return Encoding::UTF_32_LE;
        case 0x2: return Encoding::UTF_32_LE;
        case 0x3: return Encoding::UTF_32_LE;
        case 0x4: return Encoding::UTF_32_BE;
        case 0x5: return Encoding::UTF_16_LE;
        case 0x8: return Encoding::UTF_32_BE;
        case 0xA: return Encoding::UTF_16_BE;
        case 0xC: return Encoding::UTF_32_BE;
        case 0xF: return Encoding::UTF_8;
        default: return Encoding::UNKNOWN;
        }
    }
    else if (patternSize == 2)
    {
        switch (pattern)
        {
        case 0x1: return Encoding::UTF_16_LE;
        case 0x2: return Encoding::UTF_16_BE;
        case 0x3: return Encoding::UTF_8;
        default: return Encoding::UNKNOWN;
        }
    }
    else if (patternSize == 1)
    {
        return Encoding::UTF_8;
    }
    else
    {
        return Encoding::UNKNOWN;
    }
}

Encoding_t encodingFromString(const char* str, size_t len,
                              bool ignoreLastCharacter)
{
    size_t patternSize;
    if (len % 4 == 0)
        patternSize = 4;
    else if (len % 2 == 0)
        patternSize = 2;
    else
        patternSize = 1;
    unsigned anded, ored;
    if (!getBytePatterns(str, len, patternSize, anded, ored))
        return Encoding::UNKNOWN;

    Encoding_t enc1 = encodingFromPattern(anded, patternSize);
    Encoding_t enc2 = encodingFromPattern(ored, patternSize);
    if (enc1 != enc2)
        return Encoding::UNKNOWN;
    else if (enc1 != Encoding::UTF_8)
        return enc1;
    else if (Utf8::isValidUtf8(str, str + len, ignoreLastCharacter))
        return Encoding::UTF_8;
    else
        return Encoding::WINDOWS_1252;
}

Encoding_t encodingFromString(const std::string& str)
{
    return encodingFromString(str.c_str(), str.size(), false);
}

std::pair<Encoding_t, const char*> determineEncoding(
        const char* buffer, size_t length)
{
    if (length == 0)
        return std::make_pair(Encoding::UNKNOWN, buffer);
    Encoding_t encoding = encodingFromByteOrderMark(buffer, length);
    if (encoding == Encoding::UNKNOWN)
    {
        return std::make_pair(encodingFromString(buffer, length, true),
                              buffer);
    }
    else
    {
        const std::string& bom = encodingInfo(encoding)->byteOrderMark();
        return std::make_pair(encoding, buffer + bom.size());
    }
}

Encoding_t determineEncoding(std::istream& stream, size_t maxScanLength)
{
    std::streampos pos = stream.tellg();
    std::vector<char> buffer(maxScanLength);
    stream.read(&buffer[0], buffer.size());
    auto result = determineEncoding(&buffer[0], maxScanLength);
    stream.seekg(pos + std::streampos(result.second - &buffer[0]));
    return result.first;
}

}
