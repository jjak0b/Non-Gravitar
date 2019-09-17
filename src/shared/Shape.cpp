#include "Shape.hpp"
#include "Point2D.hpp"
#include "Vector.hpp"
#include "Side.hpp"
#include <cmath>

Shape::Shape() {
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

void Shape::deletePoints() {
  this->points.clear();
}

bool Shape::IsShapeColliding( Shape collision_shape ) {
  
  list<Point2D> collision_points = collision_shape.getPoints();
  std::list<Point2D>::iterator it = collision_points.begin();
  bool is_Colliding = false;

  while( !is_Colliding && it != collision_points.end() ){
    if (ray_Casting(*it)) is_Colliding = true;
    it++;
  }
  if (is_Colliding) return true;
  else return false;
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
    if ( (*it).GetY() < Ymin ) Ymin = (*it).GetY();
    if ( (*it).GetY() > Ymax ) Ymax = (*it).GetY();

  }

  if (point.GetX() < Xmin || point.GetX() > Xmax || point.GetY() < Ymin || point.GetY() > Ymax) {
    return false;
  }
        
  // conta le intersezioni del ray con i lati del poligono
  Point2D ray_A = Point2D( ( Xmin - e/point.GetY() ) , point.GetY());
  Side ray = Side(ray_A, point);
        

  it =this->points.begin();

  std::list<Point2D>::iterator surface_it, surface_next_it;
  surface_it = this->points.begin();
      
  Point2D start, end;
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
    // If they are not collinear, they must intersect in exactly one point.
    return true;
}