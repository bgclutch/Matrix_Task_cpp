find_package(GTest REQUIRED)

add_executable(tests
    unit/test.cpp
)

target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/matrix/inc
)

target_link_libraries(tests PRIVATE
    GTest::gtest
    GTest::gtest_main
)

enable_testing()
add_test(NAME unit_test COMMAND tests)
