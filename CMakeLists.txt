################################################################################
# CJson. Simple Json Parser
################################################################################
# The MIT License (MIT)
# 
# Copyright (c) 2015 Carmelo J. Fernández-Agüera Tortosa
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
################################################################################
cmake_minimum_required (VERSION 2.4)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(cjson)
set(PROJECT_VERSION 0.1.1)

option(CJSON_BUILD_TESTS "Enable building cjson test projects" OFF)
option(CJSON_BUILD_SAMPLES "Build sample projects that illusteate how to use cjson" OFF)

if(CJSON_BUILD_TESTS)
	enable_testing()
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)

# Test coverage
set(CXXFLAGS CXXFLAGS -g -O0 -Wall -fprofile-arcs -ftest-coverage)
set(CFLAGS CFLAGS -g -O0 -Wall -fprofile-arcs -ftest-coverage)
set(LDFLAGS LDFLAGS -fprofile-arcs -ftest-coverage)

endif() #GNUCXX

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

# Child projects
add_subdirectory(src) # The library itself
if(CJSON_BUILD_SAMPLES)
	add_subdirectory(samples) # The samples
endif()
if(CJSON_BUILD_TESTS)
	add_subdirectory(test) # Unit tests
endif()