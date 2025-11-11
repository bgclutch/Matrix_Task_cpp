#include "matrix.hpp"
#include <iostream>

int main() {
    using ElemType = double;
    size_t dimension;
    std::cin >> dimension;
    if (!std::cin.good() || dimension == 0) {
        std::cerr << "Illegal matrix dimension\n";
        return EXIT_FAILURE;
    }

    try {
        matrix::Matrix<ElemType> MyMatrix(dimension);
        for (size_t i = 0; i < dimension; ++i) {
            for (size_t j = 0; j < dimension; ++j) {
                ElemType num;
                if (!(std::cin >> num)) {
                    std::cerr << "Wrong matrix input data: " << num << "\n";
                    return EXIT_FAILURE;
                }
                MyMatrix[i][j] = num;
            }
        }

        ElemType matrix_determinant = MyMatrix.getDeterminant();
        std::cout << matrix_determinant << std::endl;
    } catch (const std::runtime_error& error) {
        std::cerr << "Runtime error: " << error.what() << "\n";
        return EXIT_FAILURE;
    } catch (const std::bad_alloc& error) {
        std::cerr << "Bad alloc error: " << error.what() << "\n";
        return EXIT_FAILURE;
    } catch (const std::out_of_range& error) {
        std::cerr << "Out of range error: " << error.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}