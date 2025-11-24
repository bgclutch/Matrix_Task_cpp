#pragma once

#include <utility>
#include <iostream>
#include <stdexcept>

struct Controllable {
    static int control_;
    int* resource_;

    Controllable() : resource_(new int(1)) {}

    Controllable(const Controllable& other) : resource_(nullptr) {
        if (control_ % 5 == 0) {
            control_ = 5;
            throw std::bad_alloc();
        }
        --control_;
        resource_ = new int(*other.resource_);
    }

    Controllable& operator=(const Controllable& other) {
        Controllable tmp(other);
        std::swap(*this, tmp);
        return *this;
    }

    Controllable(Controllable&& other) noexcept :
        resource_{std::exchange(other.resource_, nullptr)} {}


    Controllable& operator=(Controllable&& other) noexcept {
        std::swap(resource_, other.resource_);
        return *this;
    }

    ~Controllable() {
        delete resource_;
    }
};