#pragma once
#include "shared/Shape.hpp"
#include "shared/Point2D.hpp"

class BunkerBShape : public Shape{

    public:
        BunkerBShape(Point2D origin);
        bool ShapeCollision(Shape collision_shape);
};