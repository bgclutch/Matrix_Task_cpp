#include "matrix.hpp"
#include <iostream>

int main() {
    using ElemType = double;
    size_t dimension;
    std::cin >> dimension;
    if (!std::cin.good()) {
        std::cerr << "Illegal matrix dimension\n";
        return EXIT_FAILURE;
    }

    matrix::Matrix<ElemType> MyMatrix(dimension);

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            ElemType num;
            if (!(std::cin >> num)) {
                std::cerr << "Wrong matrix input data\n";
                return EXIT_FAILURE;
            }
            MyMatrix[i][j] = num;
        }
    }

    ElemType matrix_determinant;

    try {
        matrix_determinant = MyMatrix.getDeterminant();
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << matrix_determinant << std::endl;

    return EXIT_SUCCESS;
}