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

set(ARGP_SOURCES
    argp-parse.c
    argp-help.c
    argp-fmtstream.c
    argp-bug-address.c
    argp-program-version.c
    argp-error-exit-status.c
)

set(ARGP_HEADERS
    argp.h
    argp-namefrob.h
    argp-fmtstream.h
)

add_library(argp ${WIN_ARGP_LIB_TYPE}
    ${ARGP_SOURCES}
    ${ARGP_HEADERS}
)

target_include_directories(argp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(argp PUBLIC getopt string_helper getprogname)

if (NOT MSVC)
    target_compile_options(argp PRIVATE "-Wno-deprecated-declarations")
endif()

add_subdirectory(test)

