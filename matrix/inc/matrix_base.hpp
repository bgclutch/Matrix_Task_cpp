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

    Matrix_Base(size_t rows, size_t cols) : // constructors
         rows_{rows}
        ,cols_{cols}
        ,data_{nullptr} {
        ElemType** newData = allocateBuffer();
        used_ = rows_;
        data_ = newData;
    }

    ~Matrix_Base() { // destructor
        deleteMatrix();
    }

    Matrix_Base(Matrix_Base<ElemType>&& other) noexcept : // move constructor
         rows_{std::exchange(other.rows_, 0)}
        ,cols_{std::exchange(other.cols_, 0)}
        ,used_{std::exchange(other.used_, 0)}
        ,data_{std::exchange(other.data_, nullptr)} {}


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

    Matrix_Base(const Matrix_Base&) = delete;            // copy constructor
    Matrix_Base& operator=(const Matrix_Base&) = delete; // copy assignment

 public:
    void swap(Matrix_Base& other) noexcept {
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(used_, other.used_);
        std::swap(data_, other.data_);
    }

 protected:
    ElemType** allocateBuffer() const {
        ElemType** newData = nullptr;
        size_t used = 0;
        try {
            newData = new ElemType*[rows_];
            for (; used != rows_; ++used)
                newData[used] = new ElemType[cols_];
        } catch (std::bad_alloc&) {
            deleteTmpMemory(newData, used);
            throw;
        }
        return newData;
    }

    void deleteMatrix() noexcept {
        for (size_t i = 0; i != rows_; ++i)
            delete[] data_[i];
        delete[] data_;
        data_ = nullptr;
        used_ = 0;
    }

 private:
    static void deleteTmpMemory(ElemType** newData, size_t used) noexcept {
        if (newData) {
            for (size_t i = 0; i != used; ++i)
                delete[] newData[i];
            delete[] newData;
        }
    }
};
} // namespace matrix