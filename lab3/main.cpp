#include "Square.hpp"
#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Vector.hpp"


int main(){
    Figure* rectangle;
    Figure* square;
    Figure* trapezoid;

    if (true) {
        rectangle = new Rectangle({Point(0, 0), Point(0, 1), Point(2, 1), Point(2, 0)});
        square = new Square({Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)});
        trapezoid = new Trapezoid({Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0)});
    }
    else {
        rectangle = new Rectangle();
        square = new Square();
        trapezoid = new Trapezoid();
        std::cin >> *rectangle >> *square >> *trapezoid;
    }
    Vector vector = Vector();
    vector.pushBack(rectangle);
    vector.pushBack(square);
    vector.pushBack(trapezoid);
    if (*vector.getF(0) == *vector.getF(2)) {
        std::cout << "Equal\n";
    }
    for (size_t i = 0; i < 3; i++) {
        std::cout << *vector.getF(i) << "\n";
    }
    for (size_t i = 0; i < vector.length(); i++) {
        std::cout << (*vector.getF(i)).center() << "\n";
    }
    std::cout << vector.allArea() << "\n";
    vector.pop(0);\
    std::cout << vector.allArea() << "\n";
}
