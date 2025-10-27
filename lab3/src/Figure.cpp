#include "Figure.hpp"


Figure::Figure() : data(nullptr), size(0) {}

Figure::Figure(Point* points, const size_t size) : size(size) {
    this->data = new Point[size];
    for (size_t i = 0; i < this->size; i++) {
        this->data[i] = points[i];
        if (i > 0) {
                this->data[i - 1].setNext(&this->data[i]);
            }
    }
    this->data[this->size - 1].setNext(&this->data[0]);
} 

Figure::Figure(const std::initializer_list<Point> &points) : size(points.size()) {
    if (size > 0) {
        this->data = new Point[this->size];
        size_t i = 0;
        for (const auto& point : points) {
            this->data[i] = point;
            if (i > 0) {
                this->data[i - 1].setNext(&this->data[i]);
            }
            i++;
            if (i == this->size) {
                this->data[i - 1].setNext(&this->data[0]);
            }
        }
    }
    else {
        this->data = nullptr; 
    }
}

Figure::Figure(const Figure& other) : size(other.size) {
    this->data = new Point[this->size];
    for (size_t i = 0; i < this->size; i++) {
        this->data[i] = other.data[i];
        if (i > 0) {
            this->data[i - 1].setNext(&this->data[i]);
        }
    }
    this->data[this->size - 1].setNext(&this->data[0]);
};

Figure::Figure(Figure&& other) noexcept : size(other.size), data(other.data) {
    other.data = nullptr;
    other.size = 0;
}

Figure::~Figure() noexcept {
    delete[] this->data;
    this->data = nullptr;
    this->size = 0;
}

void Figure::validate() {}

bool operator==(const Figure& f1, const Figure& f2) {
    return f1.equal(f2);
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    if (figure.size == 0) { return os; }
    os << "Figure: ";
    for (size_t i = 0; i < figure.size; i++) {
        os << figure.data[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    delete[] figure.data;
    figure.data = nullptr;
    figure.size = 0;

    size_t size;
    std::cout << "Enter new size: ";
    is >> size;
    if (size == 0) { return is; }

    figure.size = size;
    figure.data = new Point[figure.size];

    for (size_t i = 0; i < figure.size; i++) {
        std::cout << "Point_" << i + 1 << " write: \"x y\": ";
        is >> figure.data[i];
        std::cout << "\n";
        if (i > 0) {
            figure.data[i - 1].setNext(&figure.data[i]);
        }
    }
    figure.data[figure.size - 1].setNext(&figure.data[0]);

    figure.validate();

    return is;
}
