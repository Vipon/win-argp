# MIT License
#
# Copyright (c) 2023 Konychev Valerii
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

cmake_minimum_required(VERSION 3.15)

project(win-argp
  LANGUAGES C
  VERSION 1.0
)

if (NOT WIN_ARGP_INSTALL_PREFIX)
    set(WIN_ARGP_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/win-argp")
endif (NOT WIN_ARGP_INSTALL_PREFIX)

if (NOT WIN_ARGP_LIB_TYPE)
    set(WIN_ARGP_LIB_TYPE SHARED)
endif (NOT WIN_ARGP_LIB_TYPE)

include(CTest)

include_directories(include)
install(
    FILES include/win-argp-config.h
    DESTINATION "${WIN_ARGP_INSTALL_PREFIX}/include"
)

add_subdirectory(getopt)
add_subdirectory(string_helper)
add_subdirectory(getprogname)
add_subdirectory(argp)

