set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(INCLUDE_FILES
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/allocator_commons.h
    ${PROJECT_INCLUDE_DIR}/hyundeok/allocator/sequential/sequential_allocate.h)

# file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_INCLUDE_DIR}/*.h)

set(SOURCE_FILES
    hyundeok/allocator/allocator_commons.cc
    hyundeok/allocator/sequential/sequential_allocate.cc)

# file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${PROJECT_INCLUDE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${CPP_ALLOCATOR_VERSION_MAJOR}
    PUBLIC_HEADER "${INCLUDE_FILES}")

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
