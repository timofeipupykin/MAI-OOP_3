#include "Vector.hpp"
#include "Figure.hpp"
#include <cstddef>

Vector::Vector() : data(nullptr), size(0), capacity(0) {}

Vector::Vector(Figure* value, size_t size) : size(size), capacity(size), data(new Figure*[size]) {
    for (size_t i = 0; i < size; i++) {
        this->data[i] = value;
    }
}

Vector::~Vector() noexcept {
    for (size_t i = 0; i < capacity; i++) {
        delete data[i];
    }
    delete[] data;
}

void Vector::pushBack(Figure* value) {
    if (this->size < this->capacity) {
        this->data[this->size++] = value;
    }
    else {
        if (this->capacity == 0) {
            reallocate(1);
        }
        else {
            reallocate(this->capacity * 2);
        }
        pushBack(value);
    }
}

void Vector::reallocate(size_t new_capacity) {
    Figure** data = new Figure*[new_capacity];
    for (size_t i = 0; i < this->size; i++) {
        data[i] = this->data[i];
    }
    // for (size_t i = 0; i < capacity; i++) {
    //     delete this->data[i];
    // }
    delete[] this->data;
    this->data = data;
    this->capacity = new_capacity;
}

void Vector::pop(int idx) {
    if (idx > this->size) { return; }
    this->data[idx] = nullptr;
    delete this->data[idx];
    
    for (size_t i = idx; i < this->size; i++) {
        this->data[i] = this->data[i + 1];
    }
    this->size--;
}

double Vector::allArea() {
    double area = 0.0;
    for (size_t i = 0; i < size; i++) {
        double temp = *this->data[i];
        area += temp;
    }
    return area;
}

Figure* Vector::getF(int idx) const {
    return this->data[idx];
}

size_t Vector::length() const {
    return this->size;
}