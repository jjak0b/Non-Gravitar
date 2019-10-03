#include "Shape.hpp"
#include "Point2D.hpp"
#include "Vector.hpp"
#include "Side.hpp"
#include <cmath>
#include "entities/Level.hpp"
#include "Line2D.hpp"

Shape::Shape() {
};

Shape::~Shape() {
  this->absolute_points.clear();
  this->offset_points.clear();
};


void Shape::addAbsolute( Point2D point ) {
  this->absolute_points.push_front(point);
}

void Shape::addAbsoluteList( list<Point2D> point_list ) {
  
  std::list<Point2D>::iterator it = point_list.begin();
  for (it; it !=  point_list.end(); it++) {
      addAbsolute( (*it) );
  }
}

void Shape::addOffset( Point2D point, Point2D origin ) {
  this->offset_points.push_front(point);
  origin.Add(point);
  addAbsolute(origin);
}

list<Point2D> Shape::getAbsolutes() {
  return this->absolute_points;
}
list<Point2D> Shape::getOffsetPoints() {
  return this->offset_points;
}

void Shape::deleteAbsolutes() {
  this->absolute_points.clear();
}

void Shape::UpdateAbsolutes( Point2D origin, Level *world ) {

 if ( world != NULL )  {
    Point2D point;
    list<Point2D>::iterator it_offset, it_absolute;
    it_offset = this->offset_points.begin();
    it_absolute = this->absolute_points.begin();
    
    for (; it_offset != this->offset_points.end(); it_offset++, it_absolute++ ) {
      
      point = origin;
      point.Add(*it_offset);
      
      (*it_absolute) = point;
    }
  }
}

// Intersezioni
bool Shape::IsShapeColliding( Point2D o1, Point2D o2, Shape* collision_shape, Level *world ) {
	
	Vector* ptr_bounds = NULL;
	Vector bounds;
	bounds = world->GetBounds();
	ptr_bounds = &bounds;

	VECTOR_VALUE_TYPE invert;
	invert = GetOffSet( &invert, o1, o2, 0, ptr_bounds );
	Point2D temp;
	if (invert < 0) {
		temp = o1;
		o1 = o2;
		o2 = temp;
	}

	Vector direction_v;
	direction_v = BuildDirection( o1, o2, ptr_bounds );
	Point2D direction = Point2D(0,0);
	
	this->UpdateAbsolutes(direction, world);
	direction.Add(direction_v);
	this->UpdateAbsolutes(direction, world );

	list<Point2D> collision_points = collision_shape->getAbsolutes();
	std::list<Point2D>::iterator it = collision_points.begin();
	bool is_Colliding = false;


	while( !is_Colliding && it != collision_points.end() ){
		if ( this->ray_Casting(*it, world ) ) is_Colliding = true;
		it++;
	}
// 	list<Point2D> collision_points = this->getAbsolutes();
// 	std::list<Point2D>::iterator it = collision_points.begin();
// 	bool is_Colliding = false;
//   while( !is_Colliding && it != collision_points.end() ){
//     if ( collision_shape->ray_Casting(*it, world ) ) is_Colliding = true;
//     it++;
//   }
  if (is_Colliding) return true;
  else return false;
}



	bool Shape::ray_Casting(Point2D point, Level *world ) {

  int intersections = 0;
  float e = 1.0;
  Vector* ptr_bounds = NULL;
	Vector bounds;
	bounds = world->GetBounds();
	ptr_bounds = &bounds;

  // Imposta i valori minimi e massimi del poligono
  float Xmin = this->absolute_points.front().GetX();
  float Xmax = this->absolute_points.front().GetX();
  float Ymin = this->absolute_points.front().GetY();
  float Ymax = this->absolute_points.front().GetY(); 
        
  std::list<Point2D>::iterator it = this->absolute_points.begin();
  it++;
  for (it; it !=  this->absolute_points.end(); it++) {

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
        

  it =this->absolute_points.begin();
      
  Point2D start, end;
  while( it != this->absolute_points.end() ){
    start = *it;
    it++;
    end = *it;
    Side side = Side( start, end );
    if (_areIntersecting( side, ray, world ) ) intersections ++;   }

    // Se le intersezioni sono dispari il punto è all'interno del poligono
    if ((intersections & 1) == 1) {
    // Inside of polygon
      return true;
    } else {
      // Outside of polygon
      return false;
    }
}  



// bool Shape::ray_Casting(Point2D point, Level *world ) {

//   int intersections = 0;
//   float e = 1.0;
//   Vector* ptr_bounds = NULL;
// 	Vector bounds;
// 	bounds = world->GetBounds();
// 	ptr_bounds = &bounds;

//   // Imposta i valori minimi e massimi del poligono
//   float Xmin = this->absolute_points.front().GetX();
//   float Xmax = this->absolute_points.front().GetX();
//   float Ymin = this->absolute_points.front().GetY();
//   float Ymax = this->absolute_points.front().GetY(); 
        
//   std::list<Point2D>::iterator it = this->absolute_points.begin();
//   it++;
//   VECTOR_VALUE_TYPE difference;

//   for (it; it !=  this->absolute_points.end(); it++) {
// 	GetUnitOffset( &difference, Xmin , (*it).GetX(), 0, ptr_bounds);
//     if ( difference < 0 ) // (*it).GetX() < Xmin
// 		Xmin = (*it).GetX();
// 	GetUnitOffset( &difference, Xmax , (*it).GetX(), 0, ptr_bounds);
//     if ( difference > 0 ) // (*it).GetX() > Xmax
// 		Xmax = (*it).GetX();
// 	GetUnitOffset( &difference, Ymin , (*it).GetY(), 1, NULL);
//     if ( difference < 0 ) // (*it).GetY() < Ymin
// 		Ymin = (*it).GetY();
// 	GetUnitOffset( &difference, Ymax , (*it).GetY(), 1, NULL );
//     if ( difference > 0 ) //  (*it).GetY() > Ymax
// 		Ymax = (*it).GetY();

//   }

//   Point2D point_min = Point2D( Xmin, Ymin );
//   Point2D point_max = Point2D( Xmax, Ymax );

//   VECTOR_VALUE_TYPE
//   	distance_X_point_to_X_min,
//   	distance_X_point_to_X_max,
// 	distance_Y_point_to_Y_min,
// 	distance_Y_point_to_Y_max;

// 	GetOffSet(&distance_X_point_to_X_min, point_min, point, BOUND_INDEX_WIDTH, ptr_bounds ); // point.GetX() < Xmin -> point.GetX() - Xmin < 0
// 	GetOffSet(&distance_X_point_to_X_max, point_max, point, BOUND_INDEX_WIDTH, ptr_bounds ); // point.GetX() > Xmax -> point.GetX() - Xmax > 0
// 	GetOffSet(&distance_Y_point_to_Y_min, point_min, point, BOUND_INDEX_HEIGHT, NULL ); // point.GetY() < Ymin -> point.GetY() - Ymin < 0
// 	GetOffSet(&distance_Y_point_to_Y_max, point_max, point, BOUND_INDEX_HEIGHT, NULL ); // point.GetY() > Ymax -> point.GetY() - Ymax > 0
// 	if (distance_X_point_to_X_min < 0 || distance_X_point_to_X_max > 0 || distance_Y_point_to_Y_min < 0 || distance_Y_point_to_Y_max > 0) {
// 		return false;
// 	}

//   // conta le intersezioni del ray con i lati del poligono
//   Point2D ray_A = Point2D( ( Xmin - e/point.GetY() ) , point.GetY());
//   Side ray = Side(ray_A, point);
        

// 	it =this->absolute_points.begin();
// 	Point2D start, end;
// 	while( it != this->absolute_points.end() ){
// 		start = *it;
// 		it++;
// 		end = *it;
// 		Side side = Side( start, end );
// 		if (_areIntersecting( side, ray, world) )
// 			intersections ++;
// 	}

//     // Se le intersezioni sono dispari il punto è all'interno del poligono
//     if ((intersections & 1) == 1) {
//     // Inside of polygon
//       return true;
//     } else {
//       // Outside of polygon
//       return false;
//     }
//   }  

bool AreIntersecting( Side a, Side b, Level *world  ){
	Vector bounds = world->GetBounds();
	Line2D l1 = Line2D( a, &bounds );
	Line2D l2 = Line2D( b, &bounds );
	return l1.IsIntersecting( l2 );
}

bool Shape::_areIntersecting( Side v1, Side v2, Level *world ) {
    
	Vector bounds = world->GetBounds();
    float v1x1 = v1.GetStart().GetX();
    float v1y1 = v1.GetStart().GetY();
    float v1x2 = v1.GetEnd().GetX();
    float v1y2 = v1.GetEnd().GetY();

    float v2x1 = v2.GetStart().GetX();
    float v2y1 = v2.GetStart().GetY();
    float v2x2 = v2.GetEnd().GetX();
    float v2y2 = v2.GetEnd().GetY();

    float d1, d2;
    float a1, a2, b1, b2, c1, c2;

    // Convert vector 1 to a line (line 1) of infinite length.
    // We want the line in linear equation standard form: A*x + B*y + C = 0
    // See: http://en.wikipedia.org/wiki/Linear_equation
    //GetUnitOffset(&a1, v1y1, v1y2, 1, NULL );// 
	a1 = v1y2 - v1y1;
    //GetUnitOffset(&b1, v1x2, v1x1, 0, &bounds ); // 
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
    //GetUnitOffset(&a2, v2y1, v2y2, 1, NULL ); // 
	a2 = v2y2 - v2y1;
    //GetUnitOffset(&b2, v2x2, v2x1, 0, &bounds ); //
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

bool Shape::areIntersecting( Side a, Side b, Level *world) {
	Vector bounds = world->GetBounds();
	return AreIntersecting( a, b, world);

	Vector* ptr_bounds = NULL;
	bounds = world->GetBounds();
	ptr_bounds = &bounds;

	// a = side
	// b = ray

	VECTOR_VALUE_TYPE a_x1 = a.GetStart().GetX();
	VECTOR_VALUE_TYPE a_y1 = a.GetStart().GetY();
	VECTOR_VALUE_TYPE a_x2 = a.GetEnd().GetX();
	VECTOR_VALUE_TYPE a_y2 = a.GetEnd().GetY();

	VECTOR_VALUE_TYPE b_x1 = b.GetStart().GetX();
	VECTOR_VALUE_TYPE b_y1 = b.GetStart().GetY();
	VECTOR_VALUE_TYPE b_x2 = b.GetEnd().GetX();
	VECTOR_VALUE_TYPE b_y2 = b.GetEnd().GetY();

	VECTOR_VALUE_TYPE
		*m1,
		*m2,
		q1,
		q2,
		xc, yc,
		xm, ym;

	Point2D
		point_m,
		point_c,
		point_r,
		point_k1,
		point_k2;

	VECTOR_VALUE_TYPE
		a_x_max, a_x_min, a_y_max, a_y_min,
		b_x_max, b_x_min, b_y_max, b_y_min;

	VECTOR_VALUE_TYPE
		a_distance_x_left, a_distance_x_right,
		a_distance_y_up, a_distance_y_down,
		b_distance_x_left, b_distance_x_right,
		b_distance_y_up, b_distance_y_down;

	Point2D 
		a_point_max, a_point_min,
		b_point_max, b_point_min;

	VECTOR_VALUE_TYPE distance;

	a_x_max = a_x1;
	a_x_min = a_x2;
	GetUnitOffset( &distance, a_x2, a_x1, 0, &bounds );
	if ( distance < 0) { //  a_x1 < a_x2
		a_x_max = a_x2;
		a_x_min = a_x1;
	}

	a_y_max = a_y1;
	a_y_min = a_y2;
	GetUnitOffset( &distance, a_y2, a_y1, 1, &bounds );
	if ( distance < 0) { // a_y1 < a_y2
		a_y_max = a_y2;
		a_y_min = a_y1;
	}

	b_x_max = b_x1;
	b_x_min = b_x2;
	GetUnitOffset( &distance, b_x2, b_x1, 0, &bounds );
	if ( distance < 0 ) { // b_x1 < b_x2
		b_x_max = b_x2;
		b_x_min = b_x1;
	}

	b_y_max = b_y1;
	b_y_min = b_y2;
	GetUnitOffset( &distance, b_y2, b_y1, 1, &bounds );
	if ( distance < 0 ) { // b_y1 < b_y2
		b_y_max = b_y2;
		b_y_min = b_y1;
	}
	
	a_point_max = Point2D( a_x_max, a_y_max );
	a_point_min = Point2D( a_x_min, a_y_min );
	b_point_max = Point2D( b_x_max, b_y_max );
	b_point_min = Point2D( b_x_min, b_y_min );

	// y = m2*x + q = retta ray casting
	// y = m1*x + q = il lato

	m1 = NULL;
	m2 = NULL;
	q1 = a_x1;
	q2 = b_x1;
	
	VECTOR_VALUE_TYPE a_distance_x, a_distance_y, b_distance_x, b_distance_y;

	GetUnitOffset( &a_distance_x, a_x1, a_x2, 0, ptr_bounds );
	GetUnitOffset( &a_distance_y, a_y1, a_y2, 1, ptr_bounds );
	GetUnitOffset( &b_distance_x, b_x1, b_x2, 0, ptr_bounds );
	GetUnitOffset( &b_distance_y, b_y1, b_y2, 1, ptr_bounds );

	if ( a_distance_x != 0 ) {
		m1 = new float;
		*m1 = ( a_distance_y / a_distance_x );
		q1 = a_y1 - (*m1)*(a_x1);
	}
	if ( b_distance_x != 0 ) {
		m2 = new float;
		*m2 = ( b_distance_y / b_distance_x);
		q2 = b_y1 - (*m2)*(b_x1);
	}

	// rette coincidenti o parallele verticali
	if ( ( m1 == NULL ) && ( m2 == NULL ) ) {
		if (a_x1 == b_x1) {
			float distance_bmax_up;
			float distance_bmax_down;
			float distance_bmin_up;
			float distance_bmin_down;
			
			GetOffSet( &distance_bmax_up, b_point_max, a_point_max, 1, ptr_bounds );
			GetOffSet( &distance_bmax_down, b_point_max, a_point_min, 1, ptr_bounds );
			GetOffSet( &distance_bmin_up, b_point_min, a_point_max, 1, ptr_bounds );
			GetOffSet( &distance_bmin_down, b_point_min, a_point_min, 1, ptr_bounds );
			// eiste almeno un y tale che a_y_min <= b_y_min <= a_y_max || a_y_min <= b_y_max <= a_y_max
			// <=> (a_y_min - b_y_min <= 0 && a_y_max - b_y_min >= 0) || ( a_y_min - b_y_max <= 0 && a_y_max - b_y_max >= 0 )

			// if ( (distance_bmax_down <= 0 && distance_bmax_up >= 0) || (distance_bmin_down <= 0 && distance_bmin_up >= 0 ) ) {
			if( (distance_bmin_down <= 0 && distance_bmin_up >= 0) || ( distance_bmax_down <= 0 && distance_bmax_up >= 0 ) ){
					return true;
			}
			else {
				return false;
			}
			
			// float distance_a;
			// float distance_bmax;
			// float distance_bmin;

			// GetOffSet( &distance_a, a_point_min, a_point_max, 1, ptr_bounds );
			// GetOffSet( &distance_bmax, b_point_max, a_point_max, 1, ptr_bounds );
			// GetOffSet( &distance_bmin, b_point_min, a_point_max, 1, ptr_bounds );

			// if ( (distance_bmax >= 0 && distance_bmax <= distance_a) || (distance_bmin >= 0 && distance_bmin <= distance_a)) {
			// 	return true;
			// }
			// else {
			// 	return false;
			// }
			// a_y_min <= b_y1 <= a_y_max || a_y_min <= b_y2 <= a_y_max
		}
		else {
			return false;
		}
	}
	// retta A verticale
	else if ( m1 == NULL ) {

		xc = a_x1;
		yc = (*m2)*(xc) + q2;
		point_c = Point2D(xc,yc);

	}
	// retta B verticale
	else if ( m2 == NULL ) {

		xc = b_x1;
		yc = (*m1)*(xc) + q1;
		point_c = Point2D(xc,yc);

	}
	// rette parallele o coincidenti
	else if ( *m1 == *m2 ){
		return false;
		
	}

	// nessuna retta verticale
	else {
		VECTOR_VALUE_TYPE diff_m, diff_q;
		xc = (q2 - q1) / (*m1 - *m2);
		yc = (*m1)*(xc) + q1;
		point_c = Point2D(xc,yc);

	}

		//pr punto estremo del raggio: può essere p1 o p2 in base al caso
		//raggio di point m e punto collisione deve essere inferiore o uguale al raggio di point m e pr (punto più estremo del raggio)
		world->GetNormalizedPoint(point_c);


		GetOffSet( &a_distance_x_left, point_c, a_point_min, 0, ptr_bounds );
		GetOffSet( &a_distance_x_right, point_c, a_point_max, 0, ptr_bounds );
		GetOffSet( &a_distance_y_up, point_c, a_point_max, 1, ptr_bounds );
		GetOffSet( &a_distance_y_down, point_c, a_point_min, 1, ptr_bounds );

		GetOffSet( &b_distance_x_left, point_c, b_point_min, 0, ptr_bounds );
		GetOffSet( &b_distance_x_right, point_c, b_point_max, 0, ptr_bounds );
		GetOffSet( &b_distance_y_up, point_c, b_point_max, 1, ptr_bounds );
		GetOffSet( &b_distance_y_down, point_c, b_point_min, 1, ptr_bounds );

		if ((a_distance_x_left <= 0) && (a_distance_x_right >= 0) &&
			(a_distance_y_down <= 0) && (a_distance_y_up >= 0) &&
			(b_distance_x_left <= 0) && (b_distance_x_right >= 0) &&
			(b_distance_y_down <= 0) && (b_distance_y_up >= 0)) {
			return true;
		}

		return false; 
	}
