//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

/** @file
  * @brief Defines the Encoding enum.
  */

namespace Ystring {
    /** @brief The @a Encoding struct provides a *"namespace"* for the
      *     different encoding types.
      */
    struct Encoding
    {
        enum Type
        {
            /** @brief Returned by determineEncoding when the character set
              *     can not be identified.
              */
            UNKNOWN,

            /** @brief Normal 7-bit ASCII.
              */
            ASCII,
            /** @brief UTF-8 encoding.
              */
            UTF_8,
            /** @brief ASCII extended with most characters used in
              *     Western Europe.
              */
            ISO_8859_1,
            /** @brief An alias for ISO 8859-1.
              */
            LATIN_1 = ISO_8859_1,
            /** @brief The Windows version of ISO 8859.
              */
            WINDOWS_1252,
            /** @brief The most common MS DOS encoding.
              */
            CP_437,
            /** @brief Big Endian UTF-16.
              */
            UTF_16_BE,
            /** @brief Little Endian UTF-16.
              */
            UTF_16_LE,
            /** @brief UTF-16 using the system's endianness.
              */
            UTF_16 = UTF_16_LE,
            /** @brief Big Endian UTF-32.
              */
            UTF_32_BE,
            /** @brief Little Endian UTF-32.
              */
            UTF_32_LE,
            /** @brief UTF-32 using the system's endianness.
              */
            UTF_32 = UTF_32_LE,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            UTF_7,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            UTF_1,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            UTF_EBCDIC,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            SCSU,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            BOCU_1,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            UCS_2,
            /** @brief This encoding is recognized by determineEncoding, but
              *     otherwise unsupported.
              */
            GB_18030,
            /** @brief An undetermined 8-bit character set.
              *
              * Returned by determineEncoding when the character set appears
              * to be an 8-bit encoding, but is not ASCII or UTF-8.
              */
            UNSPECIFIED_SINGLE_BYTE_CHARACTER_SET,

            MAXIMUM
        };
    };

    /** @brief An alias for Encoding::Type used throughout Ystring.
      */
    typedef Encoding::Type Encoding_t;
}
