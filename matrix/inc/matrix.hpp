#pragma once

#include "matrix_base.hpp"
#include "double_compare.hpp"
#include <cassert>
#include <iostream>

namespace matrix {
template <typename ElemType>
class Matrix final : public Matrix_Base<ElemType> {
 private:
    using Base = Matrix_Base<ElemType>;
    using Base::rows_;
    using Base::cols_;
    using Base::data_;

 private:
    class ProxyRow {
     private:
        ElemType* matrixRow_;

     public:
        explicit ProxyRow(ElemType* matrixRow) : matrixRow_(matrixRow) {}

        ElemType& operator[](size_t index) {
            return matrixRow_[index];
        }

        const ElemType& operator[](size_t index) const {
            return matrixRow_[index];
        }
    };

 public:
    using Base::Base;
    ~Matrix() override {}

    ProxyRow operator[](size_t row) {
        if (row >= rows_)
            assert(0);
        return ProxyRow(data_[row]);
    }

    static Matrix eye(size_t rows, size_t cols) {
        Matrix matrix(rows, cols);
        size_t dimension = std::min(rows, cols);

        for (size_t i = 0; i < dimension; ++i)
            matrix[i][i] = 1;
        return matrix;
    }

    static Matrix eye(size_t dimension) {
        Matrix matrix(dimension);
        for (size_t i = 0; i < dimension; ++i)
            matrix[i][i] = 1;
        return matrix;
    }

    #if 0
    double getDeterminant() {
        double determinant = 1.;
        Matrix<double> tmp(*this);

        for (size_t i = 0; i < rows_ - 1; ++i) {

        }

        return determinant;
    }
    #endif

    void swapRows(const size_t first, const size_t second) noexcept { // maybe throw exception here??
        std::swap(data_[first], data_[second]);
    }

    ElemType getTrace() const {
        ElemType res = 0;
        size_t dimension = std::min(rows_, cols_);

        for (size_t i = 0; i < dimension; ++i)
            res += data_[i][i];

        return res;
    }

    ElemType getMainDiagElemsMult() const {
        ElemType res = 1;
        size_t dimension = std::min(rows_, cols_);

        for (size_t i = 0; i < dimension; ++i)
            res *= data_[i][i];

        return res;
    }

    Matrix& negate() & {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                data_[i][j] = -data_[i][j];
            }
        }
        return *this;
    }

    size_t rows() const noexcept {
        return rows_;
    }

    size_t cols() const noexcept {
        return cols_;
    }

 public:
    #if 1
    void printMatrix() {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    #endif

};
} // namespace matrix