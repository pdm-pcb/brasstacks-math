cmake_minimum_required(VERSION 3.20)

project(
    brasstacks_math
    VERSION 0.1.0
    DESCRIPTION "Simple linear algebra library for learning and video games"
    LANGUAGES CXX C
)

add_subdirectory(src)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(tests)
endif()