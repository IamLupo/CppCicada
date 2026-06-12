cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
#set(CMAKE_CXX_COMPILER "ccache g++")

## Debug
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")

## Release
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -s -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -O2")

## Cicada project
project(cicada VERSION 1.0.0)

## Executable
add_executable(cicada
	src/core.cpp
	src/core/ProcessedText.cpp
	src/transformer/Atbash.cpp
	src/transformer/Vigenere.cpp
	src/transformer/Shift.cpp
	src/transformer/Totient.cpp
	src/transformer/Sequence.cpp
    src/util/oeis.cpp
    src/util/screen.cpp
	src/pages.cpp
    src/main.cpp
)

include_directories(cicada src)

target_link_options(cicada PRIVATE -static-libgcc -static-libstdc++)
target_compile_options(cicada PRIVATE -fno-exceptions -fno-rtti -flto -finline-functions -Wl,--gc-sections)

## Version
execute_process(
    COMMAND git rev-parse --show-toplevel
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_GIT_TOPLEVEL
    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
    COMMAND basename "${PROJECT_GIT_TOPLEVEL}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_GIT_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_GIT_BRANCH_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_GIT_BRANCH_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
    COMMAND date
    OUTPUT_VARIABLE PROJECT_COMPILE_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file(src/version.h.in ${CMAKE_SOURCE_DIR}/src/version.h @ONLY)

## Installation
install(TARGETS cicada DESTINATION bin)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/data/
    DESTINATION data
    FILES_MATCHING PATTERN "*.*")
