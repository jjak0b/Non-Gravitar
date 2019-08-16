#pragma once

#include "Point2D.hpp"

class Side {
    protected:
    Point2D a = Point2D(0,0);
    Point2D b = Point2D(0,0);

    public:

    Side(Point2D a, Point2D b);
    Point2D getA();
    Point2D getB();
};