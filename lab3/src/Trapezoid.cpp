#include "Trapezoid.hpp"
#include <cmath>
#include <cstddef>

Trapezoid::Trapezoid() : Figure() { validate(); }

Trapezoid::Trapezoid(Point* points, size_t size) : Figure(points, size) { validate(); }

Trapezoid::Trapezoid(const std::initializer_list<Point>& points) : Figure(points) { validate(); }

Trapezoid::Trapezoid(const Trapezoid& other) : Figure(other) { validate(); }

Trapezoid::Trapezoid(Trapezoid&& other) noexcept : Figure(other) { validate(); }

Trapezoid::~Trapezoid() noexcept = default;

Trapezoid& Trapezoid::operator=(const Trapezoid& other)
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

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept
{
    delete[] this->data;
    this->data = other.data;
    this->size = other.size;
    other.data = nullptr;
    other.size = 0;
    return *this;
}

Trapezoid& Trapezoid::operator=(const Figure& other)
{
    const Trapezoid* temp = dynamic_cast<const Trapezoid*>(&other);
    *this = *temp;
    return *this;
}

Trapezoid& Trapezoid::operator=(Figure&& other) noexcept
{
    Trapezoid* temp = dynamic_cast<Trapezoid*>(&other);
    *this = *temp;
    return *this;
}

double Trapezoid::absoluteArea() const {
    if (this->size < 4) { return 0.0; }

    double area;
    for (size_t i = 0; i < this->size; i++) {
        area += this->data[i].getX() * this->data[(i + 1) % this->size].getY() - this->data[(i + 1) % this->size].getX() * this->data[i].getY();
    }
    return area / 2;
}

Point Trapezoid::center() const
{
    if (this->size == 0) return Point(0, 0);
    double area = absoluteArea();
    double Cx = 0.0;
    double Cy = 0.0;
    for (size_t i = 0; i < this->size; ++i) {
        Cx += (this->data[i].getX() + this->data[(i + 1) % this->size].getX()) * (this->data[i].getX() * this->data[(i + 1) % this->size].getY() - this->data[(i + 1) % this->size].getX() * this->data[i].getY());
        Cy += (this->data[i].getY() + this->data[(i + 1) % this->size].getY()) * (this->data[i].getX() * this->data[(i + 1) % this->size].getY() - this->data[(i + 1) % this->size].getX() * this->data[i].getY());
    }
    Cx /= (6 * area);
    Cy /= (6 * area);
    return Point(Cx, Cy);
}

Trapezoid::operator double() const
{
    return std::abs(absoluteArea());
}

bool Trapezoid::equal(const Figure& other) const
{
    double f1 = *this;
    double f2 = other;    

    return std::abs(f1 - f2) < 1e-9;
}

void Trapezoid::validate() {
    if (data) {
        if (this->size != 4) {
            throw std::runtime_error("Trapezoid must have exactly 4 points");
        }
        Point vectors[4];
        for (size_t i = 0; i < 4; i++) {
            vectors[i] = Point(this->data[(i + 1) % 4].getX() - this->data[i].getX(), this->data[(i + 1) % 4].getY() - this->data[i].getY());
        }
        double vectors_abs[4];
        for (size_t i = 0; i < 4; i++) {
            vectors_abs[i] = std::sqrt(pow(vectors[i].getX(), 2) + pow(vectors[i].getY(), 2));
        }
        double angle_02 = (vectors[0].getX() * vectors[2].getX() + vectors[0].getY() * vectors[2].getY()) / (vectors_abs[0] * vectors_abs[2]);
        double angle_13 = (vectors[1].getX() * vectors[3].getX() + vectors[1].getY() * vectors[3].getY()) / (vectors_abs[1] * vectors_abs[3]);
        if ((std::abs(std::abs(angle_02) - 1) < 1e-9) == (std::abs(std::abs(angle_13) - 1) < 1e-9)) {
            throw std::runtime_error("Trapezoid must have just 2 parallel sides");
        }
    }
}