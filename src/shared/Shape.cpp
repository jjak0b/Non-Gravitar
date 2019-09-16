#include "Shape.hpp"
#include "Point2D.hpp"
#include "Vector.hpp"
#include "Side.hpp"
#include <cmath>

Shape::Shape( Point2D origin) {
    this->origin = origin;
};

list<Point2D> Shape::getPoints(){
	return this->points;
}

void Shape::addPoint( Point2D point ) {
  this->points.push_front(point);
}

void Shape::addPointList( list<Point2D> point_list ) {
  
  std::list<Point2D>::iterator it = point_list.begin();
  for (it; it !=  point_list.end(); it++) {
      addPoint( (*it) );
  }
}


    bool Shape::ray_Casting(Point2D point) {

        int intersections = 0;
        float e = 1.0;

        // Imposta i valori minimi e massimi del poligono
        float Xmin = this->points.front().GetX();
        float Xmax = this->points.front().GetX();
        float Ymin = this->points.front().GetY();
        float Ymax = this->points.front().GetY(); 
        
        std::list<Point2D>::iterator it = this->points.begin();
        it++;
        for (it; it !=  this->points.end(); it++) {

          if ( (*it).GetX() < Xmin ) Xmin = (*it).GetX();
          if ( (*it).GetX() > Xmax ) Xmax = (*it).GetX();
          if ( (*it).GetY() < Ymin ) Ymin = (*it).GetX();
          if ( (*it).GetY() > Ymax ) Ymax = (*it).GetX();

        }

        if (point.GetX() < Xmin || point.GetX() > Xmax || point.GetY() < Ymin || point.GetY() > Ymax) {
            return false;
        }
        
        // conta le intersezioni del ray con i lati del poligono
        Point2D ray_A = Point2D( ( Xmin - e/point.GetY() ) , point.GetY());
        Side ray = Side(ray_A, point);
        

        it =this->points.begin();
        // for (it; it !=  this->points.end(); it++) {
        // 	std::list<Point2D>::iterator it_next = it++;

        // 	Side side = Side( (*it), (*it_next) );
        // 	if (areIntersecting ( side, ray ) ) intersections ++;    
        // }

      std::list<Point2D>::iterator surface_it, surface_next_it;
      surface_it = this->points.begin();
      
      Point2D start, end;
      // TODO: ricontrollare
      while( surface_it != this->points.end() ){
        start = *surface_it;
        surface_it++;
        end = *surface_it;
        Side side = Side( start, end );
        if (areIntersecting ( side, ray ) ) intersections ++;   }

        // Se le intersezioni sono dispari il punto è all'interno del poligono
        if ((intersections & 1) == 1) {
            // Inside of polygon
            return true;
        } else {
            // Outside of polygon
            return false;
        }
    }   

bool Shape::areIntersecting( Side v1, Side v2) {
    
    float v1x1 = v1.getA().GetX();
    float v1y1 = v1.getA().GetY();
    float v1x2 = v1.getB().GetX();
    float v1y2 = v1.getB().GetY();

    float v2x1 = v2.getA().GetX();
    float v2y1 = v2.getA().GetY();
    float v2x2 = v2.getB().GetX();
    float v2y2 = v2.getB().GetY();

    float d1, d2;
    float a1, a2, b1, b2, c1, c2;

    // Convert vector 1 to a line (line 1) of infinite length.
    // We want the line in linear equation standard form: A*x + B*y + C = 0
    // See: http://en.wikipedia.org/wiki/Linear_equation
    a1 = v1y2 - v1y1;
    b1 = v1x1 - v1x2;
    c1 = (v1x2 * v1y1) - (v1x1 * v1y2);

    // Every point (x,y), that solves the equation above, is on the line,
    // every point that does not solve it, is not. The equation will have a
    // positive result if it is on one side of the line and a negative one 
    // if is on the other side of it. We insert (x1,y1) and (x2,y2) of vector
    // 2 into the equation above.
    d1 = (a1 * v2x1) + (b1 * v2y1) + c1;
    d2 = (a1 * v2x2) + (b1 * v2y2) + c1;

    // If d1 and d2 both have the same sign, they are both on the same side
    // of our line 1 and in that case no intersection is possible. Careful, 
    // 0 is a special case, that's why we don't test ">=" and "<=", 
    // but "<" and ">".
    if (d1 > 0 && d2 > 0) return false;
    if (d1 < 0 && d2 < 0) return false;

     // The fact that vector 2 intersected the infinite line 1 above doesn't 
    // mean it also intersects the vector 1. Vector 1 is only a subset of that
    // infinite line 1, so it may have intersected that line before the vector
    // started or after it ended. To know for sure, we have to repeat the
    // the same test the other way round. We start by calculating the 
    // infinite line 2 in linear equation standard form.
    a2 = v2y2 - v2y1;
    b2 = v2x1 - v2x2;
    c2 = (v2x2 * v2y1) - (v2x1 * v2y2);

    // Calculate d1 and d2 again, this time using points of vector 1.
    d1 = (a2 * v1x1) + (b2 * v1y1) + c2;
    d2 = (a2 * v1x2) + (b2 * v1y2) + c2;

    // Again, if both have the same sign (and neither one is 0),
    // no intersection is possible.
    if (d1 > 0 && d2 > 0) return false;
    if (d1 < 0 && d2 < 0) return false;

    // If we get here, only two possibilities are left. Either the two
    // vectors intersect in exactly one point or they are collinear, which
    // means they intersect in any number of points from zero to infinite.
    if ((a1 * b2) - (a2 * b1) == 0.0f) return true;

    // If they are not collinear, they must intersect in exactly one point.
    return true;
}

 


// void Shape::addSide( Side side ) {
//   this->sides.push_front(side);
// }


// list<Side> Shape::GetSides() {
//   return this->sides;
// }


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// bool Shape::SideCollision(Shape collision_shape) {
  
//   list<Side> sides2 = collision_shape.GetSides();
//   std::list<Side>::iterator it = this->sides.begin();
//   std::list<Side>::iterator it2 = sides2.begin();
  
//   for (it; it !=  this->sides.end(); it++) {
//      for (it2; it2 !=  sides2.end(); it2++) {
//        if (this->doIntersect((*it).getA(),(*it).getB(), (*it2).getA(),(*it2).getB())) return true;
//     }
//   }
//   return false;
// }

// bool Shape::SurfaceCollision(Point2D point) {
//   std::list<Side>::iterator it = this->sides.begin();
//    for (it; it !=  this->sides.end(); it++) {
//     if (this->doIntersect((*it).getA(),(*it).getB(), Point2D(point.GetX()-2, point.GetY()),Point2D(point.GetX()+2, point.GetY()))) return true;
//   }
//   return false;
// }

// bool Shape::PointCollision(Point2D point) {
//   std::list<Side>::iterator it = this->sides.begin();
//    for (it; it !=  this->sides.end(); it++) {
//     if (this->doIntersect((*it).getA(),(*it).getB(), point, point)) return true;
//   }
//   return false;

// }


// bool Shape::doIntersect(Point2D p1, Point2D q1, Point2D p2, Point2D q2) { 
//     // Find the four orientations needed for general and 
//     // special cases 
//     int o1 = orientation(p1, q1, p2); 
//     int o2 = orientation(p1, q1, q2); 
//     int o3 = orientation(p2, q2, p1); 
//     int o4 = orientation(p2, q2, q1); 
  
//     // General case 
//     if (o1 != o2 && o3 != o4) 
//         return true; 
  
//     // Special Cases 
//     // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
//     if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
//     // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
//     if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
//     // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
//     if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
//      // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
//     if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
//     return false; // Doesn't fall in any of the above cases 
// } 


// bool Shape::onSegment(Point2D p, Point2D q, Point2D r) { 
//     if (q.GetX() <= max(p.GetX(), r.GetX()) && q.GetX() >= min(p.GetX(), r.GetX()) && 
//         q.GetY() <= max(p.GetY(), r.GetY()) && q.GetY() >= min(p.GetY(), r.GetY())) 
//        return true; 
  
//     return false; 
// } 
  
// // To find orientation of ordered triplet (p, q, r). 
// // The function returns following values 
// // 0 --> p, q and r are colinear 
// // 1 --> Clockwise 
// // 2 --> Counterclockwise 
// int Shape::orientation(Point2D p, Point2D q, Point2D r) { 
//     // See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
//     // for details of below formula. 
//     int val = (q.GetY() - p.GetY()) * (r.GetX() - q.GetX()) - 
//               (q.GetX() - p.GetX()) * (r.GetY() - q.GetY()); 
  
//     if (val == 0) return 0;  // colinear 
  
//     return (val > 0)? 1: 2; // clock or counterclock wise 
// } 

// bool Shape::pointOnSegment(Point2D a, Point2D b, Point2D p) {

//   float ax = ( a.GetX() );
//   float ay = ( a.GetY() );
//   float bx = ( b.GetX() );
//   float by = ( b.GetY() );
//   float px = ( p.GetX() );
//   float py = ( p.GetY() );

//   float m1 = (( px - ax ) / ( py - ay ));
//   float m2 = (( bx - ax ) / ( by - ay ));
//   float epsilon = 2;

//     if (px >= (max(ax, bx )) || (px <= min(ax, bx)) || py >= (max(ay, by )) || (py <= min(ay, by)) ) return false;
//     if (abs(m1/m2 - 1) < epsilon) return true;
//     return false;
  
// }

