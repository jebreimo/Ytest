##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-05-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 2.8)
project(Ytest_Ystring)

set(PRIVATE_HEADERS
    DecoderResult.hpp
    Encoding.hpp
    FindFlags.hpp
    PlatformDetails.hpp
    Predicates.hpp
    PrivatePlatformDetails.hpp
    SplitFlags.hpp
    Utf8.hpp
    YstringDefinitions.hpp
    YstringException.hpp
    Encoded/Appender.hpp
    Encoded/DecoderAlgorithms.hpp
    Encoded/DecoderStringFunctions.hpp
    Encoded/DecoderStringFunctions-impl.hpp
    Encoded/Encoder.hpp
    Encoded/ForwardDecoder.hpp
    Encoded/ReverseDecoder.hpp
    Generic/StringReference.hpp
    Generic/GenericString.hpp
    Generic/GenericString-impl.hpp
    Generic/Range.hpp
    Generic/RangeAlgorithms.hpp
    Generic/StringTypeTraits.hpp
    Streaming/StreamOperators.hpp
    Unicode/CaseConverter.hpp
    Unicode/CaseInsensitive.hpp
    Unicode/CharClass.hpp
    Unicode/CharMap.hpp
    Unicode/CharMappingTypes.hpp
    Unicode/StandardUpperCase.hpp
    Unicode/UnicodeChars.hpp
    Unicode/UnicodePredicates.hpp
    Utf8/DecodeUtf8.hpp
    Utf8/DecodeUtf8-impl.hpp
    Utf8/EncodeUtf8.hpp
    Utf8/EncodeUtf8-impl.hpp
    Utf8/Utf8Chars.hpp
    Utf8/Utf8Encoding.hpp
    Utf8/Utf8String.hpp
    Utf16/DecodeUtf16.hpp
    Utf16/DecodeUtf16-impl.hpp
    Utf16/EncodeUtf16.hpp
    Utf16/EncodeUtf16-impl.hpp
    Utf16/Utf16Encoding.hpp
    Utf32/DecodeUtf32.hpp
    Utf32/DecodeUtf32-impl.hpp
    Utf32/EncodeUtf32.hpp
    Utf32/EncodeUtf32-impl.hpp
    Utf32/Utf32Encoding.hpp
    Utilities/Algorithms.hpp
    Utilities/Endian.hpp
    Utilities/Iterators.hpp
    Utilities/KeyFunctionAlgorithms.hpp
    Utilities/Union16.hpp
    Utilities/Union32.hpp
    Utilities/Utilities.hpp
    )

set(SOURCE_FILES
    Predicates.cpp
    YstringException.cpp
    Streaming/StreamOperators.cpp
    Unicode/CaseConverter.cpp
    Unicode/CharClass.cpp
    Unicode/CharMap.cpp
    Unicode/CharMappingTypes.cpp
    Utf8/EncodeUtf8.cpp
    Utf8/Utf8String.cpp
    )

add_library(
    ${PROJECT_NAME} OBJECT
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    )
