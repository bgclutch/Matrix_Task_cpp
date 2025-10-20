#pragma once

#include "matrix_base.hpp"
#include "double_compare.hpp"
#include <cassert>
#include <iostream>

namespace matrix {
template <typename ElemType>
class SquareMatrix final : public Matrix_Base<ElemType> {
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
    explicit SquareMatrix(size_t dimension) : Matrix_Base<ElemType>(dimension) {}
    ~SquareMatrix() override {}

    ProxyRow operator[](size_t row) {
        if (row >= rows_)
            assert(0);
        return ProxyRow(data_[row]);
    }

    static SquareMatrix eye(size_t rows) {
        SquareMatrix matrix(rows);
        for (size_t i = 0; i < rows; ++i)
            matrix[i][i] = 1;
        return matrix;
    }

/*
1. find abs max elem
2. divide every row EXCEPT THIS to coef
...
*/
    double getDeterminant() {
        double determinant = 1.;
        SquareMatrix<double> tmp(*this);

        int swapRowsCount = 0;

        for (size_t j = 0; j < cols_ - 1; ++j) {
            ElemType comparable = tmp.data_[j][j];
            size_t chosenRowInd = j;

            for (size_t i = j; i < rows_; ++i) {
                if (std::fabs(comparable) < std::fabs(tmp.data_[i][j])) {
                    comparable = tmp.data_[i][j];
                    chosenRowInd = i;
                }
            }

            if (j != chosenRowInd) {
                tmp.swapRowsByInd(j, chosenRowInd);
                ++swapRowsCount;
            }

            auto& chosenRow = tmp.data_[j];

            if (doubleCompare::isEqual(chosenRow[j], 0.))
                return 0.;

            for (size_t i = j + 1; i < rows_; ++i) {
                ElemType* row = tmp.data_[i];
                ElemType divCoef = row[j] / chosenRow[j];

                for (size_t r_ind = j; r_ind < cols_; ++r_ind) {
                    row[r_ind] -= chosenRow[r_ind] * divCoef;
                }
            }
        }

        for (size_t i = 0; i < rows_; ++i)
            determinant *= tmp.data_[i][i];

        if (swapRowsCount % 2)
            determinant = -determinant;

        return determinant;
    }

    void swapRowsByInd(const size_t first, const size_t second) noexcept { // maybe throw exception here??
        std::swap(data_[first], data_[second]);
    }

    ElemType getTrace() const {
        ElemType res = 0;

        for (size_t i = 0; i < rows_; ++i)
            res += data_[i][i];

        return res;
    }

    ElemType getMainDiagElemsMult() const {
        ElemType res = 1;

        for (size_t i = 0; i < rows_; ++i)
            res *= data_[i][i];

        return res;
    }

    SquareMatrix& negate() & {
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