#include "BunkerCShape.hpp"
#include <cstring>
#include <iostream>
#include "Point2D.hpp"

BunkerCShape::BunkerCShape(Point2D origin) : Shape(origin){

    Point2D a = Point2D(this->origin.GetX() -2, this->origin.GetY() -1);
    Point2D b = Point2D(this->origin.GetX() +2, this->origin.GetY() -1);
    Point2D c = Point2D(this->origin.GetX() -2, this->origin.GetY());
    Point2D d = Point2D(this->origin.GetX() +2, this->origin.GetY());
    Point2D e = Point2D(this->origin.GetX() , this->origin.GetY() +1 );

    this->points.push_front(a);
    this->points.push_front(b);
    this->points.push_front(c);
    this->points.push_front(d);

    Side ab = Side(a,b);
    Side bd = Side(b,d);
    Side cd = Side(c,d);
    Side ac = Side(a,c);
    Side eo = Side(e, this->origin);

    sides.push_front(ab);
    sides.push_front(bd);
    sides.push_front(cd);
    sides.push_front(ac);
    sides.push_front(eo);
}


