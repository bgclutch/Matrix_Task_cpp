#include "matrix.hpp"
#include <iostream>

int main() {
    size_t dim;
    std::cin >> dim;
    if (!std::cin.good() || dim < 0) {
        std::cerr << "Illegal matrix dimension\n";
        return EXIT_FAILURE;
    }

    matrix::Matrix<int> MyMatrix(dim);

    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            int num;
            if (!(std::cin >> num))
                assert(0);
            MyMatrix[i][j] = num;
        }
    }

    MyMatrix.printMatrix();

    return EXIT_SUCCESS;
}