#pragma once

#include <iostream>
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

    Matrix_Base(size_t rows, size_t cols, ElemType value = 0) : rows_{rows}, cols_{cols}, data_{nullptr} { // constructors
        try {
            data_ = new ElemType*[rows_];
            for (size_t i = 0; i != rows_; ++i) {
                data_[i] = new ElemType[cols_];
                std::fill(data_[i], data_[i] + cols_, value);
            }
        } catch (...) {
            whereException(__FILE__, __LINE__);
            deleteMatrix();
            throw;
        }
    }

    explicit Matrix_Base(size_t rows) :
        Matrix_Base(rows, rows) {}

    ~Matrix_Base() { // destructor
        deleteMatrix();
    }

    Matrix_Base(const Matrix_Base<ElemType>& other) : rows_{other.rows_}, cols_{other.cols_}, data_{nullptr} { // copy constructor
        data_ = dataDeepCopy(other.data_);
    }

    Matrix_Base(Matrix_Base<ElemType>&& other) noexcept : // move constructor
         rows_{std::exchange(other.rows_, 0)}
        ,cols_{std::exchange(other.cols_, 0)}
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

    ElemType*& operator[](size_t i) noexcept {
        return data_[i];
    }

    const ElemType*& operator[](size_t i) const noexcept {
        return data_[i];
    }

    void swap(Matrix_Base& other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);
    }

 protected:
    ElemType** dataDeepCopy(ElemType** src) const {
        ElemType** newData = nullptr;
        size_t i = 0;
        try {
            newData = new ElemType*[rows_];
            for (; i != rows_; ++i)
                newData[i] = new ElemType[cols_];

            for (size_t j = 0; j != rows_; ++j)
                std::copy(src[j], src[j] + cols_, newData[j]);
        } catch (...) {
            if (newData) {
                for (size_t j = 0; j != i; ++j)
                    delete[] newData[j];
                delete newData;
            }
            throw;
        }

        return newData;
    }

    void deleteMatrix() noexcept {
        for (size_t i = 0; i != rows_; ++i)
            delete[] data_[i];
        delete[] data_;
        data_ = nullptr;
    }

    void whereException (const char* file, const size_t line) const noexcept {
        std::cerr << file << ":" << line << "\n";
    }
};
} // namespace matrix