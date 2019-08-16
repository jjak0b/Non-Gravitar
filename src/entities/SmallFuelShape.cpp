#include <cstring>
#include <iostream>
#include "shared/Point2D.hpp"
#include "SmallFuelShape.hpp"

SmallFuelShape::SmallFuelShape(Point2D origin) : Shape(origin){

    Point2D a = Point2D(this->origin.GetX() , this->origin.GetY() -1);
    Point2D b = Point2D(this->origin.GetX() , this->origin.GetY() +1);

    this->points.push_front(a);
    this->points.push_front(b);

    Side ab = Side(a,b);

    sides.push_front(ab);

}