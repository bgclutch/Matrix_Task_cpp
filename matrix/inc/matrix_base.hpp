#pragma once

#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>

namespace matrix {
template <typename ElemType>
class Matrix_Base {
 protected:
    size_t rows_;
    size_t cols_;
    ElemType** data_;

 public:
    Matrix_Base(size_t rows, size_t cols, ElemType value = 0) : rows_(rows), cols_(cols) { // constructors
        data_ = new ElemType*[rows_];
        for (size_t i = 0; i < rows_; ++i) {
            data_[i] = new ElemType[cols_];
            std::fill(data_[i], data_[i] + cols_, value);
        }
    }

    explicit Matrix_Base(size_t rows, size_t cols, const std::vector<ElemType>& elements) : rows_(rows), cols_(cols) {
        if ((rows_ * cols_) != elements.size())
            throw std::invalid_argument("Matrix and vector sizes aren't same");
        data_ = new ElemType*[rows_];
        for (size_t i = 0; i < rows_; ++i) {
            data_[i] = new ElemType[cols_];
            for (size_t j = 0; j < cols_; ++j)
                data_[i][j] = elements[i * cols_ + j];
        }
    }

    explicit Matrix_Base(size_t rows) :
        Matrix_Base(rows, rows)  {}

    explicit Matrix_Base(size_t rows, const std::vector<ElemType>& elements) :
        Matrix_Base(rows, rows, elements)  {}

 public:
    virtual ~Matrix_Base() { // destructor
        this->deleteMatrix();
    }

 public:
    Matrix_Base(const Matrix_Base<ElemType>& other) : rows_(other.rows_), cols_(other.cols_) { // copy constructor
        data_ = allocatedDeepCopy(other.data_);
    }

    Matrix_Base(Matrix_Base<ElemType>&& other) noexcept : // move constructor
         rows_(std::exchange(other.rows_, 0))
        ,cols_(std::exchange(other.cols_, 0))
        ,data_(std::exchange(other.data_, nullptr)) {}

    Matrix_Base& operator=(const Matrix_Base<ElemType>& other) { // copy assignment
        if (this == &other)
            return *this;

        ElemType** tmp = other.allocatedDeepCopy(other.data_);
        this->deleteMatrix();

        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = tmp;

        return *this;
    }

    Matrix_Base& operator=(Matrix_Base<ElemType>&& other) noexcept { // move assignment
        if (this == &other)
            return *this;

        this->swapCondition(other);
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;

        return *this;
    }

    size_t rows() const noexcept {
        return rows_;
    }

    size_t cols() const noexcept {
        return cols_;
    }

    ElemType* getRow(const size_t row) {
        if (row >= rows_)
            throw std::out_of_range("attempt to get row out of range");
        return data_[row];
    }

    const ElemType* getRow(const size_t row) const {
        if (row >= rows_)
            throw std::out_of_range("attempt to get row out of range");
        return data_[row];
    }

 protected:
    void swapCondition(Matrix_Base& other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);
    }

    ElemType** allocatedDeepCopy(ElemType** src) const {
        ElemType** newData = new ElemType*[rows_];
        for (size_t i = 0; i < rows_; ++i)
            newData[i] = new ElemType[cols_];

        for (size_t i = 0; i < rows_; ++i)
            std::copy(src[i], src[i] + cols_, newData[i]);

        return newData;
    }

    void deleteMatrix() {
        for (size_t i = 0; i < rows_; ++i)
            delete[] data_[i];
        delete[] data_;
        data_ = nullptr;
    }
};
} // namespace matrix