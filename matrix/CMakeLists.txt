add_executable(matrix)

target_include_directories(matrix PRIVATE ${PROJECT_SOURCE_DIR})

target_sources(matrix PRIVATE
    main.cpp
)
