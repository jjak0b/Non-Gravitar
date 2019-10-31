#include "Shape.hpp"
#include "Segment.hpp"

Shape::Shape() {
};

Shape::~Shape() {
  this->absolute_points.clear();
  this->offset_points.clear();
};


void Shape::addAbsolute( Point2D point, ShapeAddOffsetOption option ) {
	switch ( option ){
		case ADD_BACK:
			this->absolute_points.push_back(point);
			break;
		default:
			this->absolute_points.push_front(point);
			break;
	}
}

void Shape::addOffset( Point2D point, Point2D origin, ShapeAddOffsetOption option ) {
	switch ( option ){
		case ADD_BACK:
			this->offset_points.push_back(point);
			break;
		default:
			this->offset_points.push_front(point);
			break;
	}
	
	VECTOR_VALUE_TYPE
		x = point.GetX(),
		y = point.GetY();

	// Mi tengo traccia del bounding box della figura
	if ( x < this->min_offset.GetX() )
		this->min_offset.SetX( x );
	if ( x > this->max_offset.GetX() )
		this->max_offset.SetX( x );
	if ( y < this->min_offset.GetY() )
		this->min_offset.SetY( y );
	if ( y > this->max_offset.GetY() )
		this->max_offset.SetY( y );

	origin.Add(point);
	addAbsolute(origin, option );
}

Point2D Shape::PopOffset( ShapeAddOffsetOption option ){
	Point2D offset;
	switch ( option ){
		default :
			this->absolute_points.pop_front();
			offset = this->offset_points.front();
			this->offset_points.pop_front();
			break;
		case ADD_BACK:
			this->absolute_points.pop_back();
			offset = this->offset_points.back();
			this->offset_points.pop_back();
			break;
	}

	return offset;
}

size_t Shape::GetOffsetCount(){
	return this->offset_points.size();
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

void Shape::UpdateAbsolutes( Point2D origin ) {
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

// Intersezioni
#ifdef DEBUG_COLLISION_DRAWING
bool Shape::IsShapeColliding( GameEngine* game, Point2D this_origin, Point2D shape_origin, Shape* collision_shape, Vector* bounds ) {
#else
bool Shape::IsShapeColliding( Point2D this_origin, Point2D shape_origin, Shape* collision_shape, Vector* bounds ) {
#endif
	Vector distance_offset;
	distance_offset = BuildDirection( this_origin, shape_origin, bounds );

	Point2D origin = Point2D(0,0);
	this->UpdateAbsolutes(origin);
	origin.Add(distance_offset);
	collision_shape->UpdateAbsolutes(origin);

	bool is_Colliding = false;
	list<Point2D> collision_points = collision_shape->getAbsolutes();
	std::list<Point2D>::iterator it;
#ifdef USE_COLLISION_ODD_EVEN
	it = collision_points.begin();
	while( !is_Colliding && it != collision_points.end() ){
		if ( this->IsPointInShape( *it ) )
			is_Colliding = true;
		it++;
	}
#else
	Point2D
		this_start,
		this_end,
		shape_start,
		shape_end;
	Segment
		side_of_this_shape,
		side_of_shape;
	std::list<Point2D>::iterator it_this = this->absolute_points.begin();
	this_start = this->absolute_points.back();
	while(
#ifndef DEBUG_COLLISION_DRAWING
			!is_Colliding &&
#endif
			it_this != this->absolute_points.end() ){
		this_end = *it_this;
		side_of_this_shape = Segment( this_start, this_end );

		it = collision_points.begin();
		shape_start = collision_points.back();
		while(
#ifndef DEBUG_COLLISION_DRAWING
				!is_Colliding &&
#endif
				it != collision_points.end() ){
			shape_end = *it;

			side_of_shape = Segment( shape_start, shape_end, bounds );
			is_Colliding = is_Colliding || side_of_this_shape.IsIntersecting(
#ifdef DEBUG_COLLISION_DRAWING
					game,
#endif

					side_of_shape );
			shape_start = shape_end;
			it++;
		}

		this_start = this_end;
		it_this++;
	}
#endif
	return	is_Colliding;
}

bool Shape::IsPointInShape(Point2D point) {
	/**
	 * L'algoritmo seguente si basa sulla regola Even–odd
	 * cioè l'algoritmo che conta il numero di intersezioni tra i lati del poligono,
	 * se sono dispari, allora il punto è interno, altrimenti no
	 */

 	/**
	* y0  o
	*     |\     Interno
	*     | \       |
	*     |  \      V
	* Y   |  |\-----P
	*     |  | \    |
	* y1  |  |  o   |
	*   --|--|--|---|
	*     x0 c  x1  X
	*/

	VECTOR_VALUE_TYPE
		// coordinate del bounding box
		Xmin = this->min_offset.GetX(),
		Xmax = this->max_offset.GetX(),
		Ymin = this->min_offset.GetY(),
		Ymax = this->max_offset.GetY(),

		// coordiante del punto da verificare se è interno o meno al poligono
		x = point.GetX(), y = point.GetY();

	// se il punto non si trova almeno all'interno del bounding box, allora sicuramente non sta collidendo la figura ...
	if (x < Xmin || x > Xmax ||y < Ymin || y > Ymax) {
		return false;
	}
	// altrimenti verifica la collisione in modo dettagliato controllando la posizione del punto rispetto alla retta infinita

	VECTOR_VALUE_TYPE
		// coordinate punto iniziale
		xp0, yp0,

		// coordinate punto finale
		xp1, yp1,

		// inversa del coefficiente angolare della retta
		m_inverse;

	Point2D
		start = this->absolute_points.back(),
		end;


	// indica se numero di intersezioni fatte è dispari
	// quindi al termine dell'algortmo specifica se il punto si trova all'interno del poligono
	bool inside = false;

	for( std::list<Point2D>::iterator it = this->absolute_points.begin(); it != this->absolute_points.end(); it++ ) {
		end = *it;
		Segment side = Segment( start, end );
		Segment line = Segment( side );
		xp0 = start.GetX();
		yp0 = start.GetY();
		xp1 = end.GetX();
		yp1 = end.GetY();

		// verifico che la coordinata y del punto sia interna al segmento tra i due punti
		if( (yp1>y) != (yp0>y ) ){
		// if ( ((yp0 <= y) && (yp1 > y)) || ((yp1 <= y) && (yp0 > y)) ) {
			// If so, get the point where it crosses that line. This is a simple solution
			// to a linear equation. Note that we can't get a division by zero here -
			// if yp1 == yp0 then the above if be false.

			// risolvo il fascio di rette per il punto, conoscendo che la coordinata y è sicuramente interna
			// ( y - yp0 ) = m * ( x - xp0 )
			// <=> (y- yp0) / m = ( x - xp0)
			// <=> x = ((y-yp0)/m) + xp0

			// line.GetM(&m_inverse, true );
			// VECTOR_VALUE_TYPE cross = ( (y - yp0) * m_inverse ) + xp0; // (( xp1 - xp0) * (y - yp0) / (yp1 - yp0) + xp0);
			VECTOR_VALUE_TYPE cross = ( ((xp1 - xp0)/(yp1 - yp0)) * (y - yp0) ) + xp0 ;
			// Finally check if it crosses to the left of our test point. You could equally
			// do right and it should give the same result.

			if (cross < x)
				inside = !inside;
		}

		start = end;
	}
	return inside;
}

bool Shape::ray_Casting(Point2D point) {

  int intersections = 0;
  float e = 1.0;

  // Imposta i valori minimi e massimi del poligono
  VECTOR_VALUE_TYPE Xmin = this->min_offset.GetX();
  VECTOR_VALUE_TYPE Xmax = this->max_offset.GetX();
  VECTOR_VALUE_TYPE Ymin = this->min_offset.GetY();
  VECTOR_VALUE_TYPE Ymax = this->max_offset.GetY();

  if (point.GetX() < Xmin || point.GetX() > Xmax || point.GetY() < Ymin || point.GetY() > Ymax) {
  	return false;
  }

	// conta le intersezioni del ray con i lati del poligono
  Point2D ray_A = Point2D( ( Xmin - e/point.GetY() ) , point.GetY());
  Segment ray = Segment(ray_A, point);


  bool isIntersecting = false;
  std::list<Point2D>::iterator it = this->absolute_points.begin();
  Point2D start, end;
  start = this->absolute_points.back();
  end = *it;
  while( it != this->absolute_points.end() ) {
	  Segment side = Segment(start, end);
	  // if (_areIntersecting( side, ray, world ) ) intersections ++;
	  if (_areIntersecting( side, ray ) ) isIntersecting = !isIntersecting;

	  // if (AreIntersecting(side, ray, world)) intersections++;
	  start = end;
	  it++;
	  end = *it;
  }

	return isIntersecting;
    // Se le intersezioni sono dispari il punto è all'interno del poligono
    if ((intersections & 1) == 1) {
    // Inside of polygon
      return true;
    } else {
      // Outside of polygon
      return false;
    }
}  


bool Shape::_areIntersecting( Segment v1, Segment v2 ) {

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
