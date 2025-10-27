#pragma once

#include "Figure.hpp"


class Trapezoid : public Figure {
    private:
        void validate() override;
        double absoluteArea() const;
    public:
        Trapezoid();
        Trapezoid(Point* points, size_t size = 4);
        Trapezoid(const std::initializer_list<Point>& points);

        Trapezoid(const Trapezoid& other);
        Trapezoid(Trapezoid&& other) noexcept;

        ~Trapezoid() noexcept override;

        Trapezoid& operator=(const Figure& other) override;
        Trapezoid& operator=(Figure&& other) noexcept override;

        Trapezoid& operator=(const Trapezoid& other);
        Trapezoid& operator=(Trapezoid&& other) noexcept;

        Point center() const override;
        operator double() const override;

        bool equal(const Figure& other) const override;
};