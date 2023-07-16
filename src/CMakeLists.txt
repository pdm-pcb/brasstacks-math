file(
    GLOB_RECURSE BTM_SOURCE
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
file(
    GLOB_RECURSE BTM_HEADERS
    "${CMAKE_SOURCE_DIR}/include/brasstacks_math/*.hpp"
)

add_library(
    brasstacks_math STATIC
	${BTM_SOURCE}
    ${BTM_HEADERS}
)

target_include_directories(
    brasstacks_math PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

target_precompile_headers(
    brasstacks_math PUBLIC
    ${CMAKE_SOURCE_DIR}/include/brasstacks/math/pch.hpp
)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    target_compile_options(
        brasstacks_math PUBLIC
        "-Wall"             # All, extra, and pedantic warnings
        "-Wextra"
        "-pedantic"
    )

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_options(
            brasstacks_math PUBLIC
            "-O0"       # No optimization
            "-ggdb3"    # All the gdb flags
        )
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        target_compile_options(
            brasstacks_math PUBLIC
            "-O3"           # Healthy optimization
            "-ffast-math"   # Gotta go fast
        )
    endif()
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_C_COMPILER MATCHES "clang")
        target_compile_options(
            brasstacks_math PUBLIC
            "-Wall"             # All, extra, and pedantic warnings
            "-Wextra"
            "-pedantic"
        )

        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            target_compile_options(
                brasstacks_math PUBLIC
                "-O0"       # No optimization
                "-ggdb3"    # All the gdb flags
            )
        elseif(CMAKE_BUILD_TYPE MATCHES "Release")
            target_compile_options(
                brasstacks_math PUBLIC
                "-O3"           # Healthy optimization
                "-ffast-math"   # Gotta go fast
            )
        endif()
    else()
        target_compile_definitions(
            brasstacks_math PUBLIC
            "_CRT_SECURE_NO_WARNINGS" # Ignore "may be unsafe" warnings
            "WIN64"                   # Prefer 64 bit address space
        )

        target_compile_options(
            brasstacks_math PUBLIC
            "/nologo"  # Suppress copyright message
            "/W4"	   # Warnin's
            "/wd4312"  # Disable the warning for casting to a larger size
        )

        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            target_compile_options(
                brasstacks_math PUBLIC
                "/JMC"      # Just-My-Code
                "/Zi"		# Debugging information
                "/RTC1"     # Runtime checks
                "/GS"       # Buffer overrun checks
                "/sdl"      # Security warnings
                "/Od"       # Optimization disabled
                "/diagnostics:column" # Include column in compiler messages
            )
        elseif(CMAKE_BUILD_TYPE MATCHES "Release")
            target_compile_options(
                brasstacks_math PUBLIC
                "/O2"         # Optimization not disabled =D
                "/fp:fast"    # Gotta go fast
                "/GS-"        # No buffer overrun checks
            )
        endif()
    endif()
endif()

set_target_properties(
	brasstacks_math PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON

	ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/debug/lib
    LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/debug/lib

	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/release/lib
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/release/lib
)