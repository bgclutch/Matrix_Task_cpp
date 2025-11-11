#pragma once

#include <iostream>
#include <utility>
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
    size_t used_ = 0;
    ElemType** data_;

    Matrix_Base(size_t rows, size_t cols, ElemType value = 0) : // constructors
         rows_{rows}
        ,cols_{cols}
        ,data_{nullptr} {
        try {
            data_ = new ElemType*[rows_];
            for (size_t i = 0; i != rows_; ++i, ++used_) {
                data_[i] = new ElemType[cols_];
                std::fill(data_[i], data_[i] + cols_, value);
            }
        } catch (const std::bad_alloc& error) {
            std::cerr << error.what() << "\n";
            deleteMatrix();
            throw;
        }
    }

    explicit Matrix_Base(size_t rows) :
        Matrix_Base(rows, rows) {}

    ~Matrix_Base() { // destructor
        deleteMatrix();
    }

    Matrix_Base(const Matrix_Base<ElemType>& other) : // copy constructor
         rows_{other.rows_}
        ,cols_{other.cols_}
        ,used_{other.used_}
        ,data_{nullptr} {
        data_ = dataDeepCopy(other.data_);
    }

    Matrix_Base(Matrix_Base<ElemType>&& other) noexcept : // move constructor
         rows_{std::exchange(other.rows_, 0)}
        ,cols_{std::exchange(other.cols_, 0)}
        ,used_{std::exchange(other.used_, 0)}
        ,data_{std::exchange(other.data_, nullptr)} {}

    Matrix_Base& operator=(const Matrix_Base<ElemType>& other) { // copy assignment
        if (this == &other)
            return *this;

        Matrix_Base tmp(other);
        swap(tmp);
        return *this;
    }

    Matrix_Base& operator=(Matrix_Base<ElemType>&& other) noexcept { // move assignment
        if (this == &other)
            return *this;

        swap(other);
        other.rows_ = 0;
        other.cols_ = 0;
        other.used_ = 0;
        other.data_ = nullptr;
        return *this;
    }

 public:
    size_t rows() const noexcept {
        return rows_;
    }

    size_t cols() const noexcept {
        return cols_;
    }

    size_t used() const noexcept {
        return used_;
    }

    ElemType* getRow(size_t row) {
        if (row >= rows_)
            throw std::out_of_range("Attempt to get row out of range");
        return data_[row];
    }

    const ElemType* getRow(size_t row) const {
        if (row >= rows_)
            throw std::out_of_range("Attempt to get row out of range");
        return data_[row];
    }

    ElemType*& operator[](size_t i) noexcept {
        return data_[i];
    }

    const ElemType*& operator[](size_t i) const noexcept {
        return data_[i];
    }

    void swap(Matrix_Base& other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(used_, other.used_);
        std::swap(data_, other.data_);
    }

 protected:
    ElemType** dataDeepCopy(ElemType** src) const {
        ElemType** newData = nullptr;
        size_t used = 0;
        try {
            newData = new ElemType*[rows_];
            for (size_t i = 0; i != rows_; ++i, ++used)
                newData[i] = new ElemType[cols_];

            for (size_t i = 0; i != rows_; ++i)
                std::copy(src[i], src[i] + cols_, newData[i]);
        } catch (const std::bad_alloc& error) {
            std::cerr << error.what() << "\n";
            if (newData) {
                for (size_t i = 0; i != used; ++i)
                    delete[] newData[i];
                delete[] newData;
            }
            throw;
        }
        return newData;
    }

    void deleteMatrix() noexcept {
        for (size_t i = 0; i != used_; ++i)
            delete[] data_[i];
        delete[] data_;
        data_ = nullptr;
        used_ = 0;
    }
};
} // namespace matrix