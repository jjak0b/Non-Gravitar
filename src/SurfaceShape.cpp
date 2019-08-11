#include "SurfaceShape.hpp"
#include <cstring>
#include <iostream>
#include "Point2D.hpp"

SurfaceShape::SurfaceShape(Point2D start, Point2D end) : Shape(start){

    this->points.push_front(start);
    this->points.push_front(end);
    
    Side surface_side = Side(start, end);

    this->sides.push_front(surface_side);
}

