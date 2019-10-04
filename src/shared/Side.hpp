#pragma once

#include "Point2D.hpp"

class Side {
    protected:
    Point2D start;
    Point2D end;

    public:

    Side(Point2D start = Point2D(), Point2D end = Point2D());
    Point2D GetStart();
    Point2D GetEnd();
};