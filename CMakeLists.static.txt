##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-06.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
cmake_minimum_required(VERSION 2.8)
project(Ytest)

add_definitions(-DYstring=Ytest_Ystring)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
elseif(WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif(APPLE)

add_subdirectory(Ystring)

set(SOURCE_FILES
    Ytest/AutoTest.cpp
    Ytest/AutoTestRunner.cpp
    Ytest/Error.cpp
    Ytest/Exceptions.cpp
    Ytest/Indentation.cpp
    Ytest/JUnitReport.cpp
    Ytest/MacroUtilities.cpp
    Ytest/ParseArguments.cpp
    Ytest/PathFilter.cpp
    Ytest/Session.cpp
    Ytest/StreamRedirection.cpp
    Ytest/Test.cpp
    Ytest/TextReport.cpp
    Ytest/VisualStudioReport.cpp
    Ytest/XmlWriter.cpp
    )

set(PRIVATE_HEADERS
    Ytest/Indentation.hpp
    Ytest/JUnitReport.hpp
    Ytest/PathFilter.hpp
    Ytest/StreamRedirection.hpp
    Ytest/Test.hpp
    Ytest/TextReport.hpp
    Ytest/VisualStudioReport.hpp
    Ytest/XmlWriter.hpp
    )

set(PUBLIC_HEADERS
    Ytest.hpp
    Ytest/AutoTest.hpp
    Ytest/AutoTestRunner.hpp
    Ytest/Comparers.hpp
    Ytest/Error.hpp
    Ytest/Exceptions.hpp
    Ytest/Formatters.hpp
    Ytest/Macros.hpp
    Ytest/MacroUtilities.hpp
    Ytest/ParseArguments.hpp
    Ytest/Session.hpp
    Ytest/TestScope.hpp
    Ytest/YtestMain.hpp
    )

add_library(
    ${PROJECT_NAME} STATIC
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCE_FILES}
    $<TARGET_OBJECTS:Ytest_Ystring>
    )
