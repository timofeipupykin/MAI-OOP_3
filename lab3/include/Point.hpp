#pragma once

#include <initializer_list>
#include <iostream>


class Point
{
    private:
        double x, y;
        Point* next;

    public:
        Point(double x = 0, double y = 0, Point* next = nullptr);

        Point(const std::initializer_list<int> &xy, Point* next = nullptr);

        void setNext(Point* next);

        Point* getNext() const;

        double getX() const;
        double getY() const;

        friend std::ostream& operator<<(std::ostream& os, const Point& point);
        friend std::istream& operator>>(std::istream& is, Point& point); 
};
