##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-05-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.7)
project(Ytest_Ystring)

set(PRIVATE_HEADERS
    include/Ystring/Encoding.hpp
    include/Ystring/Endianness.hpp
    include/Ystring/FindFlags.hpp
    include/Ystring/PlatformDetails.hpp
    include/Ystring/Predicates.hpp
    include/Ystring/SplitFlags.hpp
    include/Ystring/Utf8.hpp
    include/Ystring/YstringDefinitions.hpp
    include/Ystring/YstringException.hpp
    include/Ystring/Streaming/StreamOperators.hpp
    include/Ystring/Unicode/CharClass.hpp
    include/Ystring/Unicode/UnicodeChars.hpp
    include/Ystring/Unicode/UnicodePredicates.hpp
    include/Ystring/Utf/Utf8String.hpp
    src/Ystring/PrivatePlatformDetails.hpp
    src/Ystring/Encodings/DecodeUtf16-impl.hpp
    src/Ystring/Encodings/DecodeUtf16.hpp
    src/Ystring/Encodings/DecodeUtf32-impl.hpp
    src/Ystring/Encodings/DecodeUtf32.hpp
    src/Ystring/Encodings/DecodeUtf8-impl.hpp
    src/Ystring/Encodings/DecodeUtf8.hpp
    src/Ystring/Encodings/EncodeUtf16-impl.hpp
    src/Ystring/Encodings/EncodeUtf16.hpp
    src/Ystring/Encodings/EncodeUtf32-impl.hpp
    src/Ystring/Encodings/EncodeUtf32.hpp
    src/Ystring/Encodings/EncodeUtf8-impl.hpp
    src/Ystring/Encodings/EncodeUtf8.hpp
    src/Ystring/Encodings/DecoderResult.hpp
    src/Ystring/Generic/Appender.hpp
    src/Ystring/Generic/DecoderAlgorithms.hpp
    src/Ystring/Generic/DecoderStringFunctions-impl.hpp
    src/Ystring/Generic/DecoderStringFunctions.hpp
    src/Ystring/Generic/Encoder.hpp
    src/Ystring/Generic/ForwardDecoder.hpp
    src/Ystring/Generic/GenericConvert.hpp
    src/Ystring/Generic/GenericJoin.hpp
    src/Ystring/Generic/GenericSplit.hpp
    src/Ystring/Generic/GenericString-impl.hpp
    src/Ystring/Generic/GenericString.hpp
    src/Ystring/Generic/Range.hpp
    src/Ystring/Generic/RangeAlgorithms.hpp
    src/Ystring/Generic/ReverseDecoder.hpp
    src/Ystring/Generic/StringReference.hpp
    src/Ystring/Generic/StringTypeTraits.hpp
    src/Ystring/Unicode/CaseConverter.hpp
    src/Ystring/Unicode/CaseInsensitive.hpp
    src/Ystring/Unicode/CharMap.hpp
    src/Ystring/Unicode/CharMappingTypes.hpp
    src/Ystring/Unicode/StandardUpperCase.hpp
    src/Ystring/Utf/Utf16Encoding.hpp
    src/Ystring/Utf/Utf32Encoding.hpp
    src/Ystring/Utf/Utf8Chars.hpp
    src/Ystring/Utf/Utf8Encoding.hpp
    src/Ystring/Utilities/Algorithms.hpp
    src/Ystring/Utilities/Endian.hpp
    src/Ystring/Utilities/Iterators.hpp
    src/Ystring/Utilities/KeyFunctionAlgorithms.hpp
    src/Ystring/Utilities/Union16.hpp
    src/Ystring/Utilities/Union32.hpp
    src/Ystring/Utilities/Utilities.hpp
    )

set(SOURCE_FILES
    src/Ystring/Predicates.cpp
    src/Ystring/YstringException.cpp
    src/Ystring/Encodings/EncodeUtf8.cpp
    src/Ystring/Streaming/StreamOperators.cpp
    src/Ystring/Unicode/CaseConverter.cpp
    src/Ystring/Unicode/CharClass.cpp
    src/Ystring/Unicode/CharMap.cpp
    src/Ystring/Unicode/CharMappingTypes.cpp
    src/Ystring/Utf/Utf8String.cpp
    )

add_library(Ytest_Ystring OBJECT
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    )

target_compile_definitions(Ytest_Ystring
    PRIVATE
        $<$<BOOL:${MSVC}>:_SCL_SECURE_NO_WARNINGS>
        Ystring=Ytest_Ystring
    )

target_include_directories(Ytest_Ystring BEFORE
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

add_library(Ytest::Ystring ALIAS Ytest_Ystring)
