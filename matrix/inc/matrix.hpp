#pragma once

#include "matrix_base.hpp"
#include "double_compare.hpp"
#include <cassert>
#include <iostream>
#include <vector>

namespace matrix {
template <typename ElemType>
class Matrix final : public Matrix_Base<ElemType> { // TODO check isSquare in square matrix methods
 private:
    using Base = Matrix_Base<ElemType>;
    using Base::rows_;
    using Base::cols_;
    using Base::data_;
    using Base::whereException;

 public:
    explicit Matrix(size_t rows, size_t cols, ElemType value = 0) : Matrix_Base<ElemType>(rows, cols, value) {}
    explicit Matrix(size_t dimension) : Matrix_Base<ElemType>(dimension) {}

    explicit Matrix(size_t rows, size_t cols, const std::vector<ElemType>& elements) :
        Matrix_Base<ElemType>(rows, cols) {
        if ((rows_ * cols_) != elements.size())
            throw std::invalid_argument("Matrix and vector sizes aren't same");

        try {
            data_ = new ElemType*[rows_];
            for (size_t i = 0; i != rows_; ++i) {
                data_[i] = new ElemType[cols_];
                for (size_t j = 0; j != cols_; ++j)
                    data_[i][j] = elements[i * cols_ + j];
            }
        } catch (const std::bad_alloc& error) {
            printException(error, __FILE__, __LINE__);
            Base::deleteMatrix();
            throw;
        }
    }

    explicit Matrix(size_t dimension, const std::vector<ElemType>& elements) :
        Matrix<ElemType>(dimension, dimension, elements) {}

    template <typename OtherType>  // TODO requires random access iterator tag
    explicit Matrix(const Matrix<OtherType>& other) : Matrix(other.rows(), other.cols()) {
        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j)
                data_[i][j] = static_cast<ElemType>(other[i][j]);
        }
    }

    static Matrix eye(size_t rows, ElemType value = 1) {
        Matrix matrix(rows);
        for (size_t i = 0; i != rows; ++i)
            matrix[i][i] = value;
        return matrix;
    }

 private:
    class ProxyRow {
     private:
        ElemType* matrixRow_;

     public:
        explicit ProxyRow(ElemType* matrixRow) : matrixRow_{matrixRow} {}
        ElemType& operator[](size_t index) {
            return matrixRow_[index];
        }

        const ElemType& operator[](size_t index) const {
            return matrixRow_[index];
        }
    };

 public:
    ProxyRow operator[](size_t row) noexcept {
        return ProxyRow(data_[row]);
    }

    const ProxyRow operator[](size_t row) const noexcept {
        return ProxyRow(data_[row]);
    }

    ElemType getDeterminant() const { // TODO traits for doubleCompare functions
        try {
            ensureSquare();
        } catch (const std::runtime_error& error) {
            printException(error, __FILE__, __LINE__);
            throw;
        }

        double determinant = 1.;
        Matrix<double> tmp(*this);

        int swapRowsCount = 0;

        for (size_t j = 0; j != cols_ - 1; ++j) {
            ElemType comparable = tmp[j][j];
            size_t chosenRowInd = j;

            for (size_t i = j; i != rows_; ++i) {
                if (std::fabs(comparable) < std::fabs(tmp[i][j])) {
                    comparable = tmp[i][j];
                    chosenRowInd = i;
                }
            }

            if (j != chosenRowInd) {
                tmp.swapRowsByInd(j, chosenRowInd);
                ++swapRowsCount;
            }

            double* chosenRow;

            try {
                chosenRow = tmp.getRow(j);
            } catch (const std::out_of_range& error) {
                std::cerr << error.what() << "\n";
            }

            if (doubleCompare::isEqual(chosenRow[j], 0.))
                return 0.;

            for (size_t i = j + 1; i != rows_; ++i) {
                try {
                    double* row = tmp.getRow(i);
                    double divCoef = row[j] / chosenRow[j];

                    for (size_t r_ind = j; r_ind != cols_; ++r_ind) {
                        row[r_ind] -= chosenRow[r_ind] * divCoef;
                    }
                } catch (std::out_of_range& error) {
                    printException(error, __FILE__, __LINE__);
                    throw;
                }
            }
        }

        try {
            determinant = tmp.getMainDiagElemsMult();
        } catch (const std::runtime_error& error) {
            printException(error, __FILE__, __LINE__);
            throw;
        }

        if (swapRowsCount % 2)
            determinant = -determinant;

        return std::is_integral_v<ElemType> ? std::round(determinant) : determinant;
    }

    void swapRowsByInd(const size_t first, const size_t second) noexcept {
        std::swap(data_[first], data_[second]);
    }

    ElemType getTrace() const & {
        try {
            ensureSquare();
        } catch (const std::runtime_error& error) {
            printException(error, __FILE__, __LINE__);
            throw;
        }

        ElemType res = 0;
        for (size_t i = 0; i != rows_; ++i)
            res += data_[i][i];
        return res;
    }

    double getMainDiagElemsMult() const & {
        try {
            ensureSquare();
        } catch (const std::runtime_error& error) {
            printException(error, __FILE__, __LINE__);
            throw;
        }

        double res = 1;
        for (size_t i = 0; i != rows_; ++i)
            res *= data_[i][i];

        return res;
    }

    Matrix& negate() & {
        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j) {
                data_[i][j] = -data_[i][j];
            }
        }
        return *this;
    }

    void ensureSquare() const {
        if (rows_ != cols_)
            throw std::runtime_error("Matrix must be square");
    }

    void printException(const std::exception& error, const char* file, size_t line) const noexcept {
        std::cerr << error.what() << "\n";
        whereException(file, line);
    }


 public:
    #if 0
    void printMatrix() {
        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    #endif

};
} // namespace matrix