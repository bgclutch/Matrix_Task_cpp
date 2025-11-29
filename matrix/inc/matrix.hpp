#pragma once

#include "double_compare.hpp"
#include "array_memory.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

namespace matrix {
template <typename ElemType>
class Matrix final {
 private:
    size_t rows_;
    size_t cols_;
    ArrayMemory<ArrayMemory<ElemType>> data_;

 public:
    Matrix(size_t rows, size_t cols, ElemType value = ElemType()) :
         rows_{rows}
        ,cols_{cols}
        ,data_{rows} {
        for (size_t i = 0; i != rows_; ++i) {
            data_[i] = ArrayMemory<ElemType>(cols_);
            std::fill(data_[i].getData(), data_[i].getData() + cols_, value);
        }
    }

    explicit Matrix(size_t dimension) : Matrix<ElemType>(dimension, dimension) {}

    Matrix(size_t rows, size_t cols, const std::vector<ElemType>& elements) :
        Matrix<ElemType>(rows, cols) {
        if ((rows_ * cols_) != elements.size())
            throw std::invalid_argument("Matrix and vector sizes aren't same");

        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j)
                data_[i][j] = elements[i * cols_ + j];
        }
    }

    Matrix(size_t dimension, const std::vector<ElemType>& elements) :
        Matrix<ElemType>(dimension, dimension, elements) {}

    template <typename OtherType>  // TODO requires random access iterator tag
    explicit Matrix(const Matrix<OtherType>& other) : Matrix(other.rows(), other.cols()) {
        for (size_t i = 0; i != rows_; ++i) {
            for (size_t j = 0; j != cols_; ++j)
                data_[i][j] = static_cast<ElemType>(other[i][j]);
        }
    }

    Matrix(Matrix<ElemType>&& other) noexcept : // move constructor
         rows_{std::exchange(other.rows_, 0)}
        ,cols_{std::exchange(other.cols_, 0)}
        ,data_{std::move(other.data_)} {}


    Matrix& operator=(Matrix<ElemType>&& other) noexcept { // move assignment
        if (this == &other)
            return *this;

        swap(other);
        return *this;
    }

    Matrix(const Matrix<ElemType>& other) : // copy constructor
        Matrix{other.rows_, other.cols_} {
        for (size_t i = 0; i != rows_; ++i)
            std::copy(other.data_[i].getData(), other.data_[i].getData() + cols_, data_[i].getData());
    }

    Matrix& operator=(const Matrix<ElemType>& other) { // copy assignment
        Matrix tmp(other);
        this->swap(tmp);
        return *this;
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
        return ProxyRow(data_[row].getData());
    }

    const ElemType* operator[](size_t row) const noexcept {
        return data_[row].getData();

    }

    ElemType getDeterminant() const { // TODO traits for doubleCompare functions
        ensureSquare();

        double determinant = 1.;
        int swapRowsCount = 0;

        Matrix<double> tmp(*this);

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

            double* chosenRow = tmp.getRow(j);

            if (doubleCompare::isEqual(chosenRow[j], 0.))
                return 0.;

            for (size_t i = j + 1; i != rows_; ++i) {
                double* row = tmp.getRow(i);
                double divCoef = row[j] / chosenRow[j];

                for (size_t r_ind = j; r_ind != cols_; ++r_ind) {
                    row[r_ind] -= chosenRow[r_ind] * divCoef;
                }
            }
        }

        determinant = tmp.getMainDiagElemsMult();

        if (swapRowsCount % 2)
            determinant = -determinant;

        return std::is_integral_v<ElemType> ? std::round(determinant) : determinant;
    }

    void swapRowsByInd(size_t first, size_t second) noexcept {
        std::swap(data_[first], data_[second]);
    }

    ElemType getTrace() const {
        ensureSquare();

        ElemType res = 0;
        for (size_t i = 0; i != rows_; ++i)
            res += data_[i][i];
        return res;
    }

    double getMainDiagElemsMult() const & {
        ensureSquare();

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

    size_t rows() const noexcept {
        return rows_;
    }

    size_t cols() const noexcept {
        return cols_;
    }

    ElemType* getRow(size_t row) {
        if (row >= rows_)
            throw std::out_of_range("Attempt to get row out of range");
        return data_[row].getData();
    }

    const ElemType* getRow(size_t row) const {
        if (row >= rows_)
            throw std::out_of_range("Attempt to get row out of range");
        return data_[row].getData();
    }

    void swap(Matrix& other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        data_.swap(other.data_);
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