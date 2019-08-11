#include <cstring>
#include <iostream>
#include "Point2D.hpp"
#include "BigFuelShape.hpp"

BigFuelShape::BigFuelShape(Point2D origin) : Shape(origin){

    Point2D a = Point2D(this->origin.GetX() , this->origin.GetY() -1);
    Point2D b = Point2D(this->origin.GetX() , this->origin.GetY() +2);

    this->points.push_front(a);
    this->points.push_front(b);

    Side ab = Side(a,b);

    sides.push_front(ab);

}