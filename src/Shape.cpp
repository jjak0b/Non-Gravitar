#include "Shape.hpp"
#include <cstring>
#include <iostream>
#include "Point2D.hpp"
#include "Vector.hpp"
#include "GameEngine.hpp"
#include "Side.hpp"

Shape::Shape( Point2D origin) {
    this->origin = origin;
};

list<Point2D> Shape::getShapePoints(){
	return this->points;
}

list<Side> Shape::GetSides() {
  return this->sides;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Shape::SideCollision(Shape collision_shape) {
  
  list<Side> sides2 = collision_shape.GetSides();
  std::list<Side>::iterator it = this->sides.begin();
  std::list<Side>::iterator it2 = sides2.begin();
  
  for (it; it !=  this->sides.end(); it++) {
     for (it2; it2 !=  sides2.end(); it2++) {
       if (this->doIntersect((*it).getA(),(*it).getB(), (*it2).getA(),(*it2).getB())) return true;
    }
  }
  return false;
}

bool Shape::SurfaceCollision(Point2D point) {
  std::list<Side>::iterator it = this->sides.begin();
   for (it; it !=  this->sides.end(); it++) {
    if (this->doIntersect((*it).getA(),(*it).getB(), Point2D(point.GetX()-2, point.GetY()),Point2D(point.GetX()+2, point.GetY()))) return true;
  }
  return false;
}

bool Shape::PointCollision(Point2D point) {
  std::list<Side>::iterator it = this->sides.begin();
   for (it; it !=  this->sides.end(); it++) {
    if (this->doIntersect((*it).getA(),(*it).getB(), point, point)) return true;
  }
  return false;

}


bool Shape::doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2) { 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 


bool Shape::onSegment(Point2D p, Point2D q, Point2D r) { 
    if (q.GetX() <= max(p.GetX(), r.GetX()) && q.GetX() >= min(p.GetX(), r.GetX()) && 
        q.GetY() <= max(p.GetY(), r.GetY()) && q.GetY() >= min(p.GetY(), r.GetY())) 
       return true; 
  
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int Shape::orientation(Point2D p, Point2D q, Point2D r) { 
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
    // for details of below formula. 
    int val = (q.GetY() - p.GetY()) * (r.GetX() - q.GetX()) - 
              (q.GetX() - p.GetX()) * (r.GetY() - q.GetY()); 
  
    if (val == 0) return 0;  // colinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  