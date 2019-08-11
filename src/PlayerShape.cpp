#include "PlayerShape.hpp"
#include <cstring>
#include <iostream>
#include "Point2D.hpp"

PlayerShape::PlayerShape(Point2D origin) : Shape(origin){


    Point2D a = Point2D(this->origin.GetX() -3, this->origin.GetY() -1);
    Point2D b = Point2D(this->origin.GetX() + 3, this->origin.GetY() -1);
    Point2D c = Point2D(this->origin.GetX() - 3, this->origin.GetY() + 5);
    Point2D d = Point2D(this->origin.GetX() + 3, this->origin.GetY() + 5);

    this->points.push_front(a);
    this->points.push_front(b);
    this->points.push_front(c);
    this->points.push_front(d);

    Side ab = Side(a,b);
    Side bd = Side(b,d);
    Side cd = Side(c,d);
    Side ac = Side(a,c);

    sides.push_front(ab);
    sides.push_front(bd);
    sides.push_front(cd);
    sides.push_front(ac);
    


}


