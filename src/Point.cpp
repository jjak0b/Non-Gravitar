#include "Point.hpp"
#include <cmath>

Point::Point( unsigned int _size ) : Vector( _size ){}

VECTOR_VALUE_TYPE Point::DistanceSquared( Point p, Vector* bounds ){
	VECTOR_VALUE_TYPE result = 0.0;
	VECTOR_VALUE_TYPE dist = 0.0;
	if( this->size == p.size ){
		for( unsigned int i = 0; i < this->size; i++ ){
			if( GetOffSet( &dist, *this, p, i, bounds ) ){
				result += (dist * dist);
			}
		}
	}
	else{
		result = -1;
	}
	return result;
}

VECTOR_VALUE_TYPE Point::Distance( Point p, Vector* bounds ){
	VECTOR_VALUE_TYPE result = Point::DistanceSquared( p, bounds);
	if( result >= 0 ){
		result = sqrt( result );
	}
	return result;
}