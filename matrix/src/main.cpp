#include "matrix.hpp"
#include <iostream>

int main() {
    size_t dimension;
    std::cin >> dimension;
    if (!std::cin.good()) {
        std::cerr << "Illegal matrix dimension\n";
        return EXIT_FAILURE;
    }

    matrix::Matrix<double> MyMatrix(dimension);

    for (size_t i = 0; i < dimension; ++i) {
        for (size_t j = 0; j < dimension; ++j) {
            double num;
            if (!(std::cin >> num)) {
                std::cerr << "Wrong matrix input data\n";
                return EXIT_FAILURE;
            }
            MyMatrix[i][j] = num;
        }
    }

    std::cout << MyMatrix.getDeterminant() << std::endl;

    return EXIT_SUCCESS;
}