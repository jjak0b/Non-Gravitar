#include "BunkerBShape.hpp"

BunkerBShape::BunkerBShape(Point2D origin) : Shape(origin){

    Point2D a = Point2D(this->origin.GetX() -2, this->origin.GetY() -1 );
    Point2D b = Point2D(this->origin.GetX() +2, this->origin.GetY() -1 );
    
    Point2D c = Point2D(this->origin.GetX() -2, this->origin.GetY() +2 );
    Point2D d = Point2D(this->origin.GetX() +2, this->origin.GetY() +2 );
    Point2D e = Point2D(this->origin.GetX() -3, this->origin.GetY() +3 );
    Point2D f = Point2D(this->origin.GetX() +3, this->origin.GetY() +3 );
    
    this->points.push_front(a);
    this->points.push_front(b);
    this->points.push_front(c);
    this->points.push_front(d);
    this->points.push_front(e);
    this->points.push_front(f);


    Side ab = Side(a,b);
    Side bd = Side(b,d);
    Side df = Side(d,f);
    Side fe = Side(f,e);
    Side ec = Side(e,c);
    Side ca = Side(c,a);

    sides.push_front(ab);
    sides.push_front(bd);
    sides.push_front(df);
    sides.push_front(fe);
    sides.push_front(ec);
    sides.push_front(ca);
}

