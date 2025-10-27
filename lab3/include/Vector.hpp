#pragma once

#include "Figure.hpp"
#include <cstddef>

class Vector {
    private:
        Figure** data;
        size_t size;
        size_t capacity;

        void reallocate(size_t new_capacity);
    
    public:
        Vector();
        Vector(Figure* value, size_t size = 0);
        virtual ~Vector() noexcept;
        void pushBack(Figure* value);
        void pop(int idx = 0);
        double allArea();
        Figure* getF(int idx = 0) const;
        size_t length() const;
};
