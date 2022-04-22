##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-06.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 3.16)
project(Ytest VERSION 0.1.1)

# Set YTEST_MASTER_PROJECT to ON if Ystring is the root level project.
if(NOT DEFINED YTEST_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(YTEST_MASTER_PROJECT ON)
    else()
        set(YTEST_MASTER_PROJECT OFF)
    endif()
endif()

# Install option
option(YTEST_INSTALL "Generate the install target" ${YTEST_MASTER_PROJECT})

# Install option
option(YTEST_BUILD_EXAMPLES "Build the examples" ${YTEST_MASTER_PROJECT})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/Ystring)

add_library(Ytest STATIC
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
    src/Ytest/AutoTest.cpp
    src/Ytest/AutoTestRunner.cpp
    src/Ytest/Error.cpp
    src/Ytest/Formatters.cpp
    src/Ytest/Indentation.cpp
    src/Ytest/Indentation.hpp
    src/Ytest/JUnitReport.cpp
    src/Ytest/JUnitReport.hpp
    src/Ytest/MacroUtilities.cpp
    src/Ytest/ParseArguments.cpp
    src/Ytest/ParseArguments.hpp
    src/Ytest/PathFilter.cpp
    src/Ytest/PathFilter.hpp
    src/Ytest/Session.cpp
    src/Ytest/StreamRedirection.cpp
    src/Ytest/StreamRedirection.hpp
    src/Ytest/Test.cpp
    src/Ytest/Test.hpp
    src/Ytest/TextReport.cpp
    src/Ytest/TextReport.hpp
    src/Ytest/VisualStudioReport.cpp
    src/Ytest/VisualStudioReport.hpp
    src/Ytest/XmlWriter.cpp
    src/Ytest/XmlWriter.hpp
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

include(GNUInstallDirs)

target_include_directories(Ytest
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external/Ystring/include
    )

add_library(Ytest::Ytest ALIAS Ytest)

if(YTEST_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

export(TARGETS Ytest
    NAMESPACE
        Ytest::
    FILE
        YtestConfig.cmake
    )

if(YTEST_INSTALL)
    install(TARGETS Ytest
        EXPORT YtestConfig
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

    install(EXPORT YtestConfig
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

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(YtestConfigVersion.cmake
        COMPATIBILITY SameMajorVersion
        )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/YtestConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ytest
        )
endif()
