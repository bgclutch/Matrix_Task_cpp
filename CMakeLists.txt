cmake_minimum_required(VERSION 3.13)

project(matrix)
add_subdirectory(matrix)
add_subdirectory(tests)

option(ENABLE_ASAN OFF)

foreach(target matrix tests)
    target_compile_features(${target} PUBLIC cxx_std_23)
endforeach()

target_compile_options(matrix PRIVATE
$<$<CONFIG:Debug>:
    -Wall
    -Wextra
    -Wpedantic
    -DDEBUG
    -Wmissing-declarations
    -Wcast-align
    -Wshadow
    -Wsign-conversion>
)

if(ENABLE_ASAN)
    target_compile_options(matrix PRIVATE $<$<CONFIG:Debug>: -fsanitize=address>)
    target_link_options(matrix PRIVATE $<$<CONFIG:Debug>: -fsanitize=address>)
endif()