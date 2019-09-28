#pragma once

#include "Point2D.hpp"

class Side {
    protected:
    Point2D start = Point2D(0,0);
    Point2D end = Point2D(0,0);

    public:

    Side(Point2D start, Point2D end);
    Point2D GetStart();
    Point2D GetEnd();
};