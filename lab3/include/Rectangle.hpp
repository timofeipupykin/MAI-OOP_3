#pragma once

#include "Figure.hpp"
#include <cstddef>


class Rectangle : public Figure {
    private:
        void validate() override;
    
    public:
        Rectangle();
        Rectangle(Point* points, size_t size = 4);
        Rectangle(const std::initializer_list<Point>& points);

        Rectangle(const Rectangle& other);
        Rectangle(Rectangle&& other) noexcept;

        ~Rectangle() noexcept override;

        Rectangle& operator=(const Figure& other) override;
        Rectangle& operator=(Figure&& other) noexcept override;

        Rectangle& operator=(const Rectangle& other);
        Rectangle& operator=(Rectangle&& other) noexcept;

        Point center() const override;
        operator double() const override;

        bool equal(const Figure& other) const override;
};