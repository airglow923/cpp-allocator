set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(INCLUDE_FILES
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/allocator_utils.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/allocator_types.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/sequential/sequential_allocate.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/linked_list/free_list.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/linked_list/fit_search.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/linked_list/first_fit_search.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/linked_list/next_fit_search.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/linked_list/best_fit_search.h)

# file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_INCLUDE_DIR}/*.h)

set(SOURCE_FILES
    hyundeok/allocator/allocator_utils.cc
    hyundeok/allocator/sequential/sequential_allocate.cc
    hyundeok/allocator/linked_list/free_list.cc
    hyundeok/allocator/linked_list/fit_search.cc
    hyundeok/allocator/linked_list/first_fit_search.cc
    hyundeok/allocator/linked_list/next_fit_search.cc
    hyundeok/allocator/linked_list/best_fit_search.cc)

# file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(${PROJECT_NAME} SHARED "")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${PROJECT_INCLUDE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME}
    PUBLIC ${INCLUDE_FILES}
    PRIVATE ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${CPP_ALLOCATOR_VERSION_MAJOR}
    PUBLIC_HEADER "${INCLUDE_FILES}")

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Werror
        -Wcast-align
        -Wcast-qual
        -Wdiv-by-zero
        -fexceptions)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
