#include "Point.hpp"
#include <cmath>

Point::Point( unsigned int _size ) : Vector( _size ){}

double Point::DistanceSquared( Point p ){
	double result = 0.0;
	if( this->size == p.size ){
		for( unsigned int i = 0; i < this->size; i++ ){
			result += (this->data[ i ] - p.data[ i ])*(this->data[ i ] - p.data[ i ]);
		}
	}
	else{
		result = -1;
	}
	return result;
}

double Point::Distance( Point p ){
	double result = Point::DistanceSquared( p );
	if( result >= 0 ){
		result = sqrt( result );
	}
	return result;
}