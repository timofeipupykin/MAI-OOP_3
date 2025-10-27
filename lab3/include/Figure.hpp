#pragma once

#include "Point.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>


class Figure
{
    protected:
        Point* data;
        size_t size;

        virtual void validate();

    public:
        Figure();
        Figure(Point* points, const size_t size = 0);
        Figure(const std::initializer_list<Point> &points);

        Figure(const Figure& other);
        Figure(Figure&& other) noexcept;

        virtual ~Figure() noexcept;

        virtual Figure& operator=(const Figure& other) = 0;
        virtual Figure& operator=(Figure&& other) noexcept = 0;

        virtual Point center() const = 0;
        virtual operator double() const = 0;

        virtual bool equal(const Figure& other) const = 0;
        friend bool operator==(const Figure& f1, const Figure& f2);

        friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
        friend std::istream& operator>>(std::istream& is, Figure& figure);  
};
