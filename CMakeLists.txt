cmake_minimum_required(VERSION 3.0)

project(ums LANGUAGES C)

include_directories(include)

add_compile_options(-g -O3 -fPIC)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wenum-compare
    -Wfloat-equal
    -Wredundant-decls
    -Wsign-conversion
#    -Wctor-dtor-privacy
#    -Wnon-virtual-dtor
#    -Wold-style-cast
#    -Woverloaded-virtual
#    -Wsign-promo
)

add_subdirectory(src/core)
add_subdirectory(src/run)
