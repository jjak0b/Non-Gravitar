#include "Side.hpp"

Side::Side(Point2D a, Point2D b) {
    this->a = a;
    this->b = b;
}

Point2D Side::getA() {
    return this->a;
}

Point2D Side::getB() {
    return this->b;
}