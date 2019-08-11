#pragma once
#include "Shape.hpp"
#include "Point2D.hpp"

class BunkerAShape : public Shape{

    public:
        BunkerAShape(Point2D origin);
        bool ShapeCollision(Shape collision_shape);
};