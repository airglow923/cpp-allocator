cmake_minimum_required(VERSION 3.9)

find_program(CMAKE_CXX_COMPILER
             NAMES $ENV{CXX} clang++ PATHS ENV PATH NO_DEFAULT_PATH)

project(cpp-allocator
        VERSION 1.0.0
        DESCRIPTION "Different kinds of allocators implemented in C++") 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# clang-tidy
set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy"
    "-header-filter=.*"
    "-checks= \
        readability-*,-readability-braces-around-statements, \
        modernize-*"
    "-warnings-as-errors=*")

include(GNUInstallDirs)

set(INCLUDE_FILES
    include/hyundeok/allocator/sequential/sequential_allocate.h)

set(SOURCE_FILES
    src/hyundeok/allocator/sequential/sequential_allocate.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER ${INCLUDE_FILES})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
