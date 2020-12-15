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
        modernize-*,-modernize-avoid-c-arrays"
    "-warnings-as-errors=*")

# vim YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
endif()

include(GNUInstallDirs)

set(INCLUDE_FILES
    include/hyundeok/allocator/allocator_commons.h
    include/hyundeok/allocator/sequential/sequential_allocate.h)

set(SOURCE_FILES
    src/hyundeok/allocator/allocator_commons.cc
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
