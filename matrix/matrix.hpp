#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>

namespace matrix {

template <typename ElemType>
class Matrix {
 private:
    size_t dimension;
    ElemType** data;
 public:
    explicit Matrix(size_t dimension = 0) : dimension(dimension) { // constructor
        data = new ElemType*[dimension];
        for (size_t i = 0; i < dimension; ++i)
            data[i] = new ElemType[dimension]{};
    }
    // TODO value constructor, eye static constructor

    ~Matrix() { // destructor
        for (size_t i = 0; i < dimension; ++i)
            delete[] data[i];
        delete[] data;
    }

    Matrix(const Matrix<ElemType>& other) : dimension(other.dimension) { // copy constructor
        data = allocatedDeepCopy(other.data);
    }

    Matrix(Matrix<ElemType>&& other) noexcept : // move constructor
         dimension(std::exchange(other.dimension, 0))
        ,data(std::exchange(other.data, nullptr)) {}

    Matrix& operator=(const Matrix<ElemType>& other) { // copy assignment
        if (this == &other)
            return *this;

        if (dimension != other.dimension)
            assert(0); // TODO throw exception

        data = allocatedDeepCopy(other.data);
        return *this;
    }

    Matrix& operator=(Matrix<ElemType>&& other) noexcept { // move assignment
        if (this == &other)
            return *this;

        if (dimension != other.dimension)
            assert(0);  // TODO throw exception

        std::swap(data, other.data);

        return *this;
    }

    ElemType** allocatedDeepCopy(const ElemType** src) const {
        ElemType** newData = new ElemType*[dimension];
        for (auto i = 0; i < dimension; ++i)
            newData[i] = new ElemType[dimension];

        for (auto i = 0; i < dimension; ++i)
            std::copy(src[i], src[i] + dimension, newData[i]);

        return newData;
    }

 private:
    class ProxyRow {
     private:
        ElemType* matrixRow;

     public:
        explicit ProxyRow(ElemType* matrixRow) : matrixRow(matrixRow) {}

        ElemType& operator[](size_t index) {
            return matrixRow[index];
        }

        const ElemType& operator[](size_t index) const {
            return matrixRow[index];
        }
    };

 public:
    ProxyRow operator[](size_t row) {
        if (row >= dimension)
            assert(0);
        return ProxyRow(data[row]);
    }

 public:
    #if 1
    void printMatrix() {
        for (size_t i = 0; i < dimension; ++i) {
            for (size_t j = 0; j < dimension; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    #endif

};
} // namespace matrix