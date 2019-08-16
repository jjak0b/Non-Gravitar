#pragma once
#include "shared/Shape.hpp"
#include "shared/Point2D.hpp"

class SurfaceShape : public Shape{

    public:
        SurfaceShape(Point2D start, Point2D end);
};
