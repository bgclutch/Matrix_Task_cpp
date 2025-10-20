#include "matrix.hpp"
#include <iostream>

int main() {
    size_t dimension;
    std::cin >> dimension;
    if (!std::cin.good()) {
        std::cerr << "Illegal matrix dimension\n";
        return EXIT_FAILURE;
    }

    matrix::SquareMatrix<double> MyMatrix(dimension);

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            int num;
            if (!(std::cin >> num))
                assert(0);
            MyMatrix[i][j] = num;
        }
    }

    MyMatrix.printMatrix();
    std::cout << std::endl;

    std::cout << "det:" << MyMatrix.getDeterminant() << std::endl;

    // auto NewMatrix = matrix::SquareMatrix<double>::eye(5);
    // NewMatrix.printMatrix();

    // std::cout << MyMatrix.getMainDiagElemsMult() << " " << MyMatrix.getTrace() << std::endl;

    return EXIT_SUCCESS;
}