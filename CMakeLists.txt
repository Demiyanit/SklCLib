cmake_minimum_required(VERSION 3.22)

project(sklc_lib
    VERSION 0.0.1
    LANGUAGES C
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

if(MSVC)
    add_compile_options(
        /W4 # Enable all warnings.
        /ws4201 # Allow unnamed structs/unions.
        # Don't suggest the _s nonsence functions.
        /D_CRT_SECURE_NO_WARNINGS
        /D_CRT_SECURE_NO_WARNINGS_GLOBALS
        /D_CRT_NONSTDC_NO_WARNINGS
    )
else()
    add_compile_options(
        -Wall
        -Werror=return-type
        -Wshadow
        -Wconversion
        -Wno-unused
        -fsanitize=address
        -g
        -D_CRT_SECURE_NO_WARNINGS
    )
    add_link_options(-fsanitize=address)
endif()

file(GLOB_RECURSE SRCS
    "${PROJECT_SOURCE_DIR}/src/*"
    "${PROJECT_SOURCE_DIR}/include/*"
)

# comment

add_executable(sklc_lib ${SRCS})
set_property(TARGET sklc_lib PROPERTY C_STANDARD 17)
set_property(TARGET sklc_lib PROPERTY C_STANDARD_REQUIRED true)
target_include_directories(sklc_lib PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
)