#include "gtest/gtest.h"
#include "matrix.hpp"

TEST(MATRIX_BASE, copy_ctor_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(7, 10);
    auto copy_matrix = matrix;
    ASSERT_EQ(matrix[1][1], copy_matrix[5][5]);
}

TEST(MATRIX_BASE, move_ctor_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(7, 10);
    auto moved_matrix = std::move(matrix);
    ASSERT_EQ(moved_matrix[5][5], 10);
}

TEST(MATRIX_BASE, copy_assign_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(7, 10);
    auto another_matrix = matrix::SquareMatrix<int>::eye(2);
    another_matrix = matrix;
    ASSERT_EQ(another_matrix.rows(), matrix.rows());
}

TEST(MATRIX_BASE, move_assign_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(7, 10);
    auto another_matrix = matrix::SquareMatrix<int>::eye(2);
    another_matrix = std::move(matrix);
    ASSERT_EQ(another_matrix.rows(), 7);
}

TEST(MATRIX_API, eye_ctor_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(5);
    ASSERT_EQ(matrix[1][1], matrix[4][4]);
}

TEST(MATRIX_API, eye_ctor_value_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(10, 10);
    ASSERT_EQ(matrix[8][8], 10);
}

TEST(MATRIX_API, negate_matirix_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(5);
    matrix.negate();
    ASSERT_EQ(matrix[3][3], -1);
}

TEST(MATRIX_API, proxy_class_test) {
    auto matrix = matrix::SquareMatrix<int>::eye(5);
    matrix[4][2] = 42;
    ASSERT_EQ(matrix[4][2], 42);
}

#if 0
TEST(MATRIX_API, int_determinant_founder) {
    matrix::SquareMatrix<int> matrix();

}

TEST(MATRIX_API, floating_determinant_founder) {
    matrix::SquareMatrix<float> matrix();
}
#endif

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}