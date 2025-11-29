#pragma once

#include <algorithm>
#include <utility>

namespace matrix {
template <typename ElemType>
class ArrayMemory {
 private:
    ElemType* encapsulatedData_ = nullptr;
    size_t len_;

 public:
    ArrayMemory() = default;

    explicit ArrayMemory(size_t len) : len_(len) {
        encapsulatedData_ = new ElemType[len_];
    }

    ArrayMemory(const ArrayMemory& other) = delete;
    ArrayMemory& operator=(const ArrayMemory& other) = delete;

    ArrayMemory(ArrayMemory&& other) noexcept :
         encapsulatedData_{std::exchange(other.encapsulatedData_, nullptr)}
        ,len_{std::exchange(other.len_, 0)} {}

    ArrayMemory& operator=(ArrayMemory&& other) noexcept {
        if (this == &other)
            return *this;

        swap(other);
        return *this;
    }

    ElemType& operator[](size_t index) {
        return encapsulatedData_[index];
    }

    const ElemType& operator[](size_t index) const {
        return encapsulatedData_[index];
    }

    ElemType* getData() noexcept {
        return encapsulatedData_;
    }

    const ElemType* getData() const noexcept {
        return encapsulatedData_;
    }

    size_t getLen() const noexcept {
        return len_;
    }

    void swap(ArrayMemory& other) {
        std::swap(encapsulatedData_, other.encapsulatedData_);
        std::swap(len_, other.len_);
    }

    ~ArrayMemory() {
        delete[] encapsulatedData_;
    }
};
}