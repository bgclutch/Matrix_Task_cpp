#include "matrix.hpp"
#include <iostream>

int main() {
    size_t rows, cols;
    std::cin >> rows >> cols;
    if (!std::cin.good()) {
        std::cerr << "Illegal matrix dimension\n";
        return EXIT_FAILURE;
    }

    matrix::Matrix<double> MyMatrix(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            int num;
            if (!(std::cin >> num))
                assert(0);
            MyMatrix[i][j] = num;
        }
    }

    MyMatrix.printMatrix();

    auto NewMatrix = matrix::Matrix<double>::eye(5);
    NewMatrix.printMatrix();

    std::cout << MyMatrix.getMainDiagElemsMult() << " " << MyMatrix.getTrace() << std::endl;

    return EXIT_SUCCESS;
}