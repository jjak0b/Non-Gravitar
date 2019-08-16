#pragma once
#include "shared/Shape.hpp"
#include "shared/Point2D.hpp"

class BunkerAShape : public Shape{

    public:
        BunkerAShape(Point2D origin);
        bool ShapeCollision(Shape collision_shape);
};