cmake_minimum_required(VERSION 3.20)

project(
    brasstacks_math
    VERSION 0.1.0
    DESCRIPTION "Simple linear algebra library for learning and video games"
    LANGUAGES CXX C
)

add_subdirectory(src)
add_subdirectory(tests)