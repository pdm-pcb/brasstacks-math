cmake_minimum_required(VERSION 3.20) # This minimum requirement allows us to not
                                     # worry whether CMake is automatically
                                     # adding the RTTI enable flag to an MSVC
                                     # build

project(
    brasstacks_math
    VERSION 0.1.0
    DESCRIPTION "Simple linear algebra library for learning and video games"
    LANGUAGES CXX C
)

add_subdirectory(src)
add_subdirectory(tests)