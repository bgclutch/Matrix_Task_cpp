#include "gtest/gtest.h"
#include "matrix.hpp"
#include "controllable.hpp"
#include <vector>

int Controllable::control_ = 5;

TEST(MATRIX_BASE, copy_ctor_test) {
    auto matrix = matrix::Matrix<int>::eye(7, 10);
    auto copy_matrix = matrix;
    ASSERT_EQ(matrix[1][1], copy_matrix[5][5]);
}

TEST(MATRIX_BASE, move_ctor_test) {
    auto matrix = matrix::Matrix<int>::eye(7, 10);
    auto moved_matrix = std::move(matrix);
    ASSERT_EQ(moved_matrix[5][5], 10);
}

TEST(MATRIX_BASE, copy_assign_test) {
    auto matrix = matrix::Matrix<int>::eye(7, 10);
    auto another_matrix = matrix::Matrix<int>::eye(2);
    another_matrix = matrix;
    ASSERT_EQ(another_matrix.rows(), matrix.rows());
}

TEST(MATRIX_BASE, move_assign_test) {
    auto matrix = matrix::Matrix<int>::eye(7, 10);
    auto another_matrix = matrix::Matrix<int>::eye(2);
    another_matrix = std::move(matrix);
    ASSERT_EQ(another_matrix.rows(), 7);
}

TEST(MATRIX_API, eye_ctor_test) {
    auto matrix = matrix::Matrix<int>::eye(5);
    ASSERT_EQ(matrix[1][1], matrix[4][4]);
}

TEST(MATRIX_API, eye_ctor_value_test) {
    auto matrix = matrix::Matrix<int>::eye(10, 10);
    ASSERT_EQ(matrix[8][8], 10);
}

TEST(MATRIX_API, negate_matirix_test) {
    auto matrix = matrix::Matrix<int>::eye(5);
    matrix.negate();
    ASSERT_EQ(matrix[3][3], -1);
}

TEST(MATRIX_API, proxy_class_test) {
    auto matrix = matrix::Matrix<int>::eye(5);
    matrix[4][2] = 42;
    ASSERT_EQ(matrix[4][2], 42);
}

TEST(MATRIX_API, operator_square_scope_test) {
    auto matrix = matrix::Matrix<int>(6, 4, 42);
    matrix[4][2] = 24;
    ASSERT_EQ(matrix[4][2], 24);
}

TEST(MATRIX_EXCEPTIONS, getTrace_exception_test) {
    auto matrix = matrix::Matrix<int>(6, 4, 42);
    EXPECT_THROW(matrix.getTrace(), std::runtime_error);
}

TEST(MATRIX_EXCEPTIONS, getRow_exception_test) {
    auto matrix = matrix::Matrix<int>(2, 2);
    EXPECT_THROW(matrix.getRow(2), std::out_of_range);
}

TEST(MATRIX_EXCEPTIONS, getDeterminant_exception_test) {
    std::vector<int> elements {9, 2, 3, 4, 15, 6};
    auto matrix = matrix::Matrix<int>(2, 3, elements);
    EXPECT_THROW(matrix.getDeterminant(), std::runtime_error);
}

TEST(MATRIX_EXCEPTIONS, getMainDiagElemsMult_exception_test) {
    std::vector<int> elements {9, 2, 3, 4, 15, 6};
    auto matrix = matrix::Matrix<int>(2, 3, elements);
    EXPECT_THROW(matrix.getMainDiagElemsMult(), std::runtime_error);
}

TEST(MATRIX_EXCEPTIONS, dataDeepCopy_exception_test) {
    auto matrix1 = matrix::Matrix<int>(2, 2);
    bool isThrown = false;
    try {
        auto matrix2 = matrix1;
    } catch (const std::out_of_range& error) {
        isThrown = true;
    }
    ASSERT_FALSE(isThrown);
}

TEST(MATRIX_EXCEPTIONS, matrix_template_ctor_excepiton_test) {
    auto matrix1 = matrix::Matrix<int>(6);
    EXPECT_NO_THROW(matrix::Matrix<double> matrix2(matrix1));
}

TEST(MATRIX_EXCEPTIONS, matrix_and_vector_sizes) {
    std::vector<int> elements{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    EXPECT_THROW(matrix::Matrix<int>(13, elements), std::invalid_argument);
}

TEST(MATRIX_EXCEPTIONS, copy_ctor_exception) {
    Controllable::control_ = 6;
    bool isThrown = false;

    try {
        auto matrix1 = matrix::Matrix<Controllable>{3};
        auto matrix2(matrix1);
    } catch (std::bad_alloc& error) {
        isThrown = true;
    }

    ASSERT_TRUE(isThrown);
}

TEST(MATRIX_EXCEPTIONS, copy_assignment_exception) {
    Controllable::control_ = 9;
    bool isThrown = false;

    try {
        auto matrix1 = matrix::Matrix<Controllable>{2, 3};
        auto matrix2 = matrix1;
    } catch (std::bad_alloc& error) {
        isThrown = true;
    }

    ASSERT_TRUE(isThrown);
}

TEST(MATRIX_DETERMINANT, float_determinant_founder) {
    std::vector<double> data = {
        12, 2, -170, 1742, -8, -2, -9, -10, -3, 5,
        8, 2, -17, 536, -2, 0, -2, -3, -1, 1,
        22, -8, -306, 1608, -14, 3, -5, -7, 1, 3,
        8, -4, -34, 0, -2, 2, 1, 0, 1, -1,
        20, -2, -153, 1139, -8, 3, -3, -6, 0, 2,
        58, -6, -459, 3283, -23, 10, -8, -17, 0, 6,
        -24, -12, -51, -1675, 3, 2, 7, 10, 5, -3,
        -38, 2, 493, -4154, 23, 1, 19, 23, 5, -11,
        -2, 0, 17, -335, 1, 1, 2, 2, 1, -1,
        6, -2, -68, 402, -3, 1, -1, -2, 0, 1
    };

    matrix::Matrix<double> matrix(10, data);
    ASSERT_TRUE(doubleCompare::isEqual(matrix.getDeterminant(), 4556));
}

TEST(MATRIX_DETERMINANT, int_determinant_founder) {
    std::vector<int> data = {
        12, 2, -170, 1742, -8, -2, -9, -10, -3, 5,
        8, 2, -17, 536, -2, 0, -2, -3, -1, 1,
        22, -8, -306, 1608, -14, 3, -5, -7, 1, 3,
        8, -4, -34, 0, -2, 2, 1, 0, 1, -1,
        20, -2, -153, 1139, -8, 3, -3, -6, 0, 2,
        58, -6, -459, 3283, -23, 10, -8, -17, 0, 6,
        -24, -12, -51, -1675, 3, 2, 7, 10, 5, -3,
        -38, 2, 493, -4154, 23, 1, 19, 23, 5, -11,
        -2, 0, 17, -335, 1, 1, 2, 2, 1, -1,
        6, -2, -68, 402, -3, 1, -1, -2, 0, 1
    };

    matrix::Matrix<int> matrix(10, data);
    ASSERT_EQ(matrix.getDeterminant(), 4556);
}

TEST(MATRIX_DETERMINANT, find_matrix_1) {
    std::vector<int> data = {14, 15, 16, 17};
    matrix::Matrix<int> matrix(2, data);

    ASSERT_EQ(matrix.getDeterminant(), -2);
}

TEST(MATRIX_DETERMINANT, find_matrix_2) {
    std::vector<double> data = {
        8180.627334555369, -6831.092903566726, 26334.869144551878, -134.7138781584852, -1416.0404521548967,
        27078.686504592846, -22744.605081047015, 87361.04225105884, -477.7083504082621, -4894.529972287412,
        2506.1087680785718, -1956.9451126154602, 7873.620614110752, -7.917359577336612, -221.4488518523916,
        -1607.2694715995829, 1463.6127111420506, -5347.716822148405, 56.337861492440744, 468.2865708953589,
        6077.050787890941, -4773.831948675019, 19133.282065869455, -26.003735495215977, -581.3468994558089
    };
    matrix::Matrix<double> matrix(5, data);

    ASSERT_TRUE(doubleCompare::isEqual(matrix.getDeterminant(), 42));
}

TEST(MATRIX_DETERMINANT, find_matrix_3) {
    std::vector<int> data = {
        -212, -133,
        -94, 154};
    matrix::Matrix<int> matrix(2, data);

    ASSERT_EQ(matrix.getDeterminant(), -45150);
}

TEST(MATRIX_DETERMINANT, find_matrix_4) {
    std::vector<double> data = {
        729.6542800000926, 391.5809887659281, 500.2610320287538, 4808.524710684705, 575.249978755065, 608.8975321191002, 636.2367823318986,
        304.6578330187471, 165.04007182485313, 208.7037661184376, 2035.6275354369895, 215.8261642346577, 263.0696403017616, 277.0777399196544,
        53.2309144270227, 32.17254287407567, 30.76936502774526, 337.11974826569235, 26.628811244833628, 88.74334265564511, 43.52594964223626,
        -12.343163025794565, -7.31836240552376, -7.409653071869533, -50.97805883432699, -28.68421591424136, 16.65866908660512, 1.7045930698274994,
        12.813752012913604, 7.303123830385558, 7.339464294324694, 79.71753422022286, -3.5149766817865142, 7.214326362058916, 13.53397432623987,
        0.6794583638566078, -0.7150294413497893, 0.6328386577445005, -9.265186604619412, 13.289990582295106, -0.20230019597966753, -4.98846977461523,
        17.91056736906623, 13.292379364554542, 6.603135452294989, 104.89023113106911, -1.8081093052178758, 57.08420791217224, 12.969652861541771
    };
    matrix::Matrix<double> matrix(7, data);

    ASSERT_TRUE(doubleCompare::isEqual(matrix.getDeterminant(), 555));
}

TEST(MATRIX_DETERMINANT, find_matrix_5) {
    std::vector<long long> data = {
        134, -86, -270,
        97, 69, 86,
        42, -144, -145
    };
    matrix::Matrix<long long> matrix(3, data);

    ASSERT_EQ(matrix.getDeterminant(), 3352384);
}

TEST(MATRIX_DETERMINANT, find_matrix_6) {
    std::vector<long double> data = {
        212.35, 128.59,
        -68.77, -256.63
    };
    matrix::Matrix<long double> matrix(2, data);

    ASSERT_TRUE(doubleCompare::isEqual(matrix.getDeterminant(), -45652.2462));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}