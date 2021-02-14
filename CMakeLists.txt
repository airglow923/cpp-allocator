cmake_minimum_required(VERSION 3.9)

set(CPP_ALLOCATOR_VERSION_MAJOR 1)
set(CPP_ALLOCATOR_VERSION_MINOR 0)
set(CPP_ALLOCATOR_VERSION_PATCH 0)

string(CONCAT PRJ_VER
    "${CPP_ALLOCATOR_VERSION_MAJOR}"
    ".${CPP_ALLOCATOR_VERSION_MINOR}"
    ".${CPP_ALLOCATOR_VERSION_PATCH}")

project(cpp-allocator
    VERSION ${PRJ_VER}
    DESCRIPTION "Different kinds of allocators implemented in C++") 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_COMPILE_FLAGS
		-Wall
		-Wextra
		-Werror
		-Wcast-align
		-Wcast-qual
		-Wdiv-by-zero
		-fexceptions)

EXECUTE_PROCESS(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    OUTPUT_VARIABLE clang_full_version_string )
string (REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1"
    CLANG_VERSION_STRING ${clang_full_version_string})

# if Clang is 10 and above and clang-tidy is found, run clang-tidy
if (CLANG_VERSION_STRING GREATER_EQUAL 10)
  find_program(CLANG_TIDY_FOUND NAMES clang-tidy)
  if (CLANG_TIDY_FOUND)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy --header-filter=.*)
  endif()
endif()

# vim YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
      ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()

add_library(${PROJECT_NAME} SHARED)

target_compile_options(${PROJECT_NAME} PRIVATE ${PROJECT_COMPILE_FLAGS})

add_subdirectory(include)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        src)

target_sources(${PROJECT_NAME}
    PUBLIC ${INCLUDE_FILES}
    PRIVATE ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${CPP_ALLOCATOR_VERSION_MAJOR}
    PUBLIC_HEADER "${INCLUDE_FILES}")

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

enable_testing()
add_subdirectory(test)
