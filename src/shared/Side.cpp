#include "Side.hpp"

Side::Side(Point2D start, Point2D end) {
    this->start = start;
    this->end = end;
}

Point2D Side::GetStart() {
    return this->start;
}

Point2D Side::GetEnd() {
    return this->end;
}