#include "Point.hpp"

Point::Point(double x, double y, Point* next) : x(x), y(y), next(next) {}

Point::Point(const std::initializer_list<int> &xy, Point* next) : x(0), y(0), next(next) {
    auto it = xy.begin();
    if (xy.size() > 0) { this->x = *it++; }
    if (xy.size() > 1) { this->y = *it; }
}

void Point::setNext(Point* next) {
    this->next = next;
}

Point* Point::getNext() const {
    return this->next;
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "Point(" << point.x << "," << point.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}