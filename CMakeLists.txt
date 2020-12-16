cmake_minimum_required(VERSION 3.9)

set(CPP_ALLOCATOR_VERSION_MAJOR 1)
set(CPP_ALLOCATOR_VERSION_MINOR 0)
set(CPP_ALLOCATOR_VERSION_PATCH 0)

string(CONCAT PRJ_VER
    "${CPP_ALLOCATOR_VERSION_MAJOR}"
    ".${CPP_ALLOCATOR_VERSION_MINOR}"
    ".${CPP_ALLOCATOR_VERSION_PATCH}")

find_program(CMAKE_CXX_COMPILER
    NAMES $ENV{CXX} clang++ PATHS ENV PATH NO_DEFAULT_PATH)

project(cpp-allocator
    VERSION ${PRJ_VER}
    DESCRIPTION "Different kinds of allocators implemented in C++") 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# clang-tidy
set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy"
    "-header-filter=.*"
    "-checks= \
        readability-*,-readability-braces-around-statements, \
        modernize-*,-modernize-avoid-c-arrays"
    "-warnings-as-errors=*")

# vim YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
      ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
