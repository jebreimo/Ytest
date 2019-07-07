##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-06.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.13)
project(Ytest)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/Ystring)

set(SOURCE_FILES
    src/Ytest/AutoTest.cpp
    src/Ytest/AutoTestRunner.cpp
    src/Ytest/Error.cpp
    src/Ytest/Formatters.cpp
    src/Ytest/Indentation.cpp
    src/Ytest/JUnitReport.cpp
    src/Ytest/MacroUtilities.cpp
    src/Ytest/ParseArguments.cpp
    src/Ytest/PathFilter.cpp
    src/Ytest/Session.cpp
    src/Ytest/StreamRedirection.cpp
    src/Ytest/Test.cpp
    src/Ytest/TextReport.cpp
    src/Ytest/VisualStudioReport.cpp
    src/Ytest/XmlWriter.cpp
    )

set(PRIVATE_HEADERS
    src/Ytest/Indentation.hpp
    src/Ytest/JUnitReport.hpp
    src/Ytest/ParseArguments.hpp
    src/Ytest/PathFilter.hpp
    src/Ytest/StreamRedirection.hpp
    src/Ytest/Test.hpp
    src/Ytest/TextReport.hpp
    src/Ytest/VisualStudioReport.hpp
    src/Ytest/XmlWriter.hpp
    )

set(PUBLIC_HEADERS
    include/Ytest/AutoTest.hpp
    include/Ytest/AutoTestRunner.hpp
    include/Ytest/Comparers.hpp
    include/Ytest/Error.hpp
    include/Ytest/Exceptions.hpp
    include/Ytest/Formatters.hpp
    include/Ytest/Macros.hpp
    include/Ytest/MacroUtilities.hpp
    include/Ytest/Session.hpp
    include/Ytest/TestScope.hpp
    include/Ytest/Ytest.hpp
    include/Ytest/YtestMain.hpp
    )

add_library(
    Ytest STATIC
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    $<TARGET_OBJECTS:Ytest::Ystring>
    )

target_compile_definitions(Ytest
    PRIVATE
        $<$<BOOL:${MSVC}>:_SCL_SECURE_NO_WARNINGS>
        Ystring=Ytest_Ystring
    )

set_target_properties(Ytest
    PROPERTIES
        DEBUG_OUTPUT_NAME "Ytest.debug"
    )

target_include_directories(Ytest
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external/Ystring/include
    )

add_library(Ytest::Ytest ALIAS Ytest)

add_subdirectory(examples)

export(TARGETS Ytest
    NAMESPACE Ytest::
    FILE YtestConfig.cmake)

export(PACKAGE Ytest)

include(GNUInstallDirs)

install(TARGETS Ytest
    EXPORT YtestTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(EXPORT YtestTargets
    FILE
        YtestConfig.cmake
    NAMESPACE
        Ytest::
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/Ytest
    )

install(
    DIRECTORY
        include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
    )
