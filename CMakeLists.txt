cmake_minimum_required(VERSION 3.5.0)

find_program(CMAKE_CXX_COMPILER
  NAMES $ENV{CXX} clang++ PATHS ENV PATH NO_DEFAULT_PATH)

project(cpp-allocator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# clang-tidy
set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=.;
    -checks=*,-fuchsia-trailing-return;
    -warnings-as-errors=*;)

set(SMARTSTRUCTURE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE STRING "")
