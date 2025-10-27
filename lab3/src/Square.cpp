#include "Square.hpp"
#include <cmath>
#include <cstddef>

Square::Square() : Figure() { validate(); }

Square::Square(Point* points, size_t size) : Figure(points, size) { validate(); }

Square::Square(const std::initializer_list<Point>& points) : Figure(points) { validate(); }

Square::Square(const Square& other) : Figure(other) { validate(); }

Square::Square(Square&& other) noexcept : Figure(other) { validate(); }

Square::~Square() noexcept = default;

Square& Square::operator=(const Square& other)
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

Square& Square::operator=(Square&& other) noexcept
{
    delete[] this->data;
    this->data = other.data;
    this->size = other.size;
    other.data = nullptr;
    other.size = 0;
    return *this;
}

Square& Square::operator=(const Figure& other)
{
    const Square* temp = dynamic_cast<const Square*>(&other);
    *this = *temp;
    return *this;
}

Square& Square::operator=(Figure&& other) noexcept
{
    Square* temp = dynamic_cast<Square*>(&other);
    *this = *temp;
    return *this;
}

Point Square::center() const
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

Square::operator double() const
{
    if (this->size < 4) { return 0.0; }

    const Point p1 = this->data[0];
    const Point p3 = this->data[2];
    double area = std::abs(p1.getX() - p3.getX()) * std::abs(p1.getY() - p3.getY());

    return area;
}

bool Square::equal(const Figure& other) const
{
    double f1 = *this;
    double f2 = other;    

    return std::abs(f1 - f2) < 1e-9;
}

void Square::validate() {
    if (data) {
        if (this->size != 4) {
            throw std::runtime_error("Square must have exactly 4 points");
        }
        Point vectors[4];
        for (size_t i = 0; i < 4; i++) {
            vectors[i] = Point(this->data[(i + 1) % 4].getX() - this->data[i].getX(), this->data[(i + 1) % 4].getY() - this->data[i].getY());
        }
        int vector_length = sqrt(pow(vectors[0].getX(), 2) + pow(vectors[0].getY(), 2));
        for (size_t i = 0; i < 4; i++) {
            int dot_product = vectors[i].getX() * vectors[(i + 1) % 4].getX() + vectors[i].getY() * vectors[(i + 1) % 4].getY();
            int other_vector_length = sqrt(pow(vectors[i].getX(), 2) + pow(vectors[i].getY(), 2));
            if (other_vector_length != vector_length) {
                throw std::runtime_error("Square must have equal sides");
            }
            if (dot_product != 0) {
                throw std::runtime_error("Square must have 90 degree angles");
            }
        }
    }
}