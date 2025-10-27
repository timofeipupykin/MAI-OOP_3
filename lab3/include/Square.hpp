#pragma once

#include "Figure.hpp"


class Square : public Figure {
    private:
        void validate() override;
    public:
        Square();
        Square(Point* points, size_t size = 4);
        Square(const std::initializer_list<Point>& points);

        Square(const Square& other);
        Square(Square&& other) noexcept;

        ~Square() noexcept override;

        Square& operator=(const Figure& other) override;
        Square& operator=(Figure&& other) noexcept override;

        Square& operator=(const Square& other);
        Square& operator=(Square&& other) noexcept;

        Point center() const override;
        operator double() const override;

        bool equal(const Figure& other) const override;
};