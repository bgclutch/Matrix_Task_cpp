add_executable(matrix)

target_include_directories(matrix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_sources(matrix PRIVATE
    src/main.cpp
    src/double_compare.cpp
)
