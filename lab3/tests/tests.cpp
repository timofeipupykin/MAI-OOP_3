#include <gtest/gtest.h>
#include "Point.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Trapezoid.hpp"
#include "Vector.hpp"

// =====================================================
//                 Point Tests
// =====================================================
TEST(PointTest, BasicAccessors) {
    Point p(3.5, 7.1);
    ASSERT_EQ(p.getX(), 3.5);
    ASSERT_EQ(p.getY(), 7.1);
}

TEST(PointTest, NextPointer) {
    Point a(1, 2);
    Point b(3, 4);
    a.setNext(&b);
    ASSERT_EQ(a.getNext(), &b);
}

// =====================================================
//                 Rectangle Tests
// =====================================================
TEST(RectangleTest, AreaAndCenter) {
    Rectangle r({ {0,0}, {4,0}, {4,3}, {0,3} });
    double area = static_cast<double>(r);
    ASSERT_NEAR(area, 12.0, 1e-9);

    Point c = r.center();
    ASSERT_NEAR(c.getX(), 2.0, 1e-9);
    ASSERT_NEAR(c.getY(), 1.5, 1e-9);
}

TEST(RectangleTest, CopyAndMove) {
    Rectangle r1({ {0,0}, {4,0}, {4,3}, {0,3} });
    Rectangle r2 = r1;
    ASSERT_TRUE(r1 == r2);

    Rectangle r3 = std::move(r1);
    ASSERT_NEAR(static_cast<double>(r3), 12.0, 1e-9);
}

TEST(RectangleTest, InvalidPointsThrows) {
    EXPECT_THROW(Rectangle({ {0,0}, {1,1}, {2,2}, {3,3} }), std::runtime_error);
}

// =====================================================
//                 Square Tests
// =====================================================
TEST(SquareTest, AreaAndCenter) {
    Square s({ {0,0}, {2,0}, {2,2}, {0,2} });
    double area = static_cast<double>(s);
    ASSERT_NEAR(area, 4.0, 1e-9);

    Point c = s.center();
    ASSERT_NEAR(c.getX(), 1.0, 1e-9);
    ASSERT_NEAR(c.getY(), 1.0, 1e-9);
}

TEST(SquareTest, EqualOperator) {
    Square s1({ {0,0}, {2,0}, {2,2}, {0,2} });
    Square s2({ {0,0}, {2,0}, {2,2}, {0,2} });
    Square s3({ {0,0}, {3,0}, {3,3}, {0,3} });
    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 == s3);
}

TEST(SquareTest, InvalidSquareThrows) {
    EXPECT_THROW(Square({ {0,0}, {3,0}, {2,2}, {0,2} }), std::runtime_error);
}

// =====================================================
//                 Trapezoid Tests
// =====================================================
TEST(TrapezoidTest, AreaAndCenter) {
    // Прямая трапеция: нижнее основание 4, верхнее 2, высота 2
    Trapezoid t({ Point(0,0), Point(4,0), Point(3,2), Point(1,2) });
    double area = static_cast<double>(t);
    ASSERT_NEAR(area, 6.0, 1e-9);

    Point c = t.center();
    ASSERT_NEAR(c.getX(), 2.0, 1e-9);
    ASSERT_NEAR(c.getY(), 0.8888888888888884, 1e-9);
}

TEST(TrapezoidTest, InvalidTrapezoidThrows) {
    // Параллелограмм — обе пары сторон параллельны
    EXPECT_THROW(Trapezoid({ Point(0,0), Point(4,0), Point(5,2), Point(1,2) }), std::runtime_error);
}

// =====================================================
//                 Vector Tests
// =====================================================
TEST(VectorTest, PushBackAndLength) {
    Vector vec;
    vec.pushBack(new Square({ {0,0}, {2,0}, {2,2}, {0,2} }));
    vec.pushBack(new Rectangle({ {0,0}, {4,0}, {4,3}, {0,3} }));

    ASSERT_EQ(vec.length(), 2);
    ASSERT_NEAR(static_cast<double>(*vec.getF(0)), 4.0, 1e-9);
    ASSERT_NEAR(static_cast<double>(*vec.getF(1)), 12.0, 1e-9);
}

TEST(VectorTest, AllAreaSum) {
    Vector vec;
    vec.pushBack(new Square({ {0,0}, {2,0}, {2,2}, {0,2} })); // 4
    vec.pushBack(new Rectangle({ {0,0}, {4,0}, {4,3}, {0,3} })); // 12
    vec.pushBack(new Trapezoid({ {0,0}, {4,0}, {3,2}, {1,2} })); // 6
    ASSERT_NEAR(vec.allArea(), 22.0, 1e-9);
}

TEST(VectorTest, PopRemovesElement) {
    Vector vec;
    vec.pushBack(new Square({ {0,0}, {2,0}, {2,2}, {0,2} }));
    vec.pushBack(new Square({ {0,0}, {3,0}, {3,3}, {0,3} }));
    ASSERT_EQ(vec.length(), 2);
    vec.pop(0);
    ASSERT_EQ(vec.length(), 1);
}

// =====================================================
//                 Main
// =====================================================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
