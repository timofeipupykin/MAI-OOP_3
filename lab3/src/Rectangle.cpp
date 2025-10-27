#include "Rectangle.hpp"
#include <cstddef>

Rectangle::Rectangle() : Figure() { validate(); }

Rectangle::Rectangle(Point* points, size_t size) : Figure(points, size) { validate(); }

Rectangle::Rectangle(const std::initializer_list<Point>& points) : Figure(points) { validate(); }

Rectangle::Rectangle(const Rectangle& other) : Figure(other) { validate(); }

Rectangle::Rectangle(Rectangle&& other) noexcept : Figure(other) { validate(); }

Rectangle::~Rectangle() noexcept = default;

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    delete[] this->data;
    this->size = other.size;
    this->data = new Point[this->size];
    for (size_t i = 0; i < this->size; ++i) {
        this->data[i] = other.data[i];
        if (i > 0)
            this->data[i - 1].setNext(&this->data[i]);
    }
    if (this->size > 0)
        this->data[this->size - 1].setNext(&this->data[0]);
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept
{
    delete[] this->data;
    this->data = other.data;
    this->size = other.size;
    other.data = nullptr;
    other.size = 0;
    return *this;
}

Rectangle& Rectangle::operator=(const Figure& other)
{
    const Rectangle* temp = dynamic_cast<const Rectangle*>(&other);
    *this = *temp;
    return *this;
}

Rectangle& Rectangle::operator=(Figure&& other) noexcept
{
    Rectangle* temp = dynamic_cast<Rectangle*>(&other);
    *this = *temp;
    return *this;
}

Point Rectangle::center() const
{
    if (this->size == 0) return Point(0, 0);

    double sumX = 0;
    double sumY = 0;
    for (size_t i = 0; i < this->size; ++i) {
        sumX += this->data[i].getX();
        sumY += this->data[i].getY();
    }

    return Point(sumX / this->size, sumY / this->size);
}

Rectangle::operator double() const
{
    if (this->size < 4) { return 0.0; }

    const Point p1 = this->data[0];
    const Point p3 = this->data[2];
    double area = std::abs(p1.getX() - p3.getX()) * std::abs(p1.getY() - p3.getY());

    return area;
}

bool Rectangle::equal(const Figure& other) const
{
    double f1 = *this;
    double f2 = other;    

    return std::abs(f1 - f2) < 1e-9;
}

void Rectangle::validate() {
    if (data) {
        if (this->size != 4) {
            throw std::runtime_error("Rectangle must have exactly 4 points");
        }
        Point vectors[4];
        for (size_t i = 0; i < 4; i++) {
            vectors[i] = Point(this->data[(i + 1) % 4].getX() - this->data[i].getX(), this->data[(i + 1) % 4].getY() - this->data[i].getY());
        }
        for (size_t i = 0; i < 4; i++) {
            int dot_product = vectors[i].getX() * vectors[(i + 1) % 4].getX() + vectors[i].getY() * vectors[(i + 1) % 4].getY();
            if (dot_product != 0) {
                throw std::runtime_error("Rectangle must have 90 degree angles");
            }
        }
    }
}
