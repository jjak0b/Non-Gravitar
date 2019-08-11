#pragma once
#include "Shape.hpp"
#include "Point2D.hpp"

class SurfaceShape : public Shape{

    public:
        SurfaceShape(Point2D start, Point2D end);
};
