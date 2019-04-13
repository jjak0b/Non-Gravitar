#include "Vector.hpp"
#include <stddef.h>
#include <cmath>

Vector::Vector( unsigned int _size ){
	this->size = _size;
	if( _size > 0 ){
		this->data = new VECTOR_TYPE[ _size ];
	}
}

unsigned int Vector::GetSize(){
	return this->size;
}

void Vector::Get( unsigned int i, VECTOR_TYPE *return_value ){
	if( i < this->size && return_value != NULL ){
		*return_value = this->data[ i ];
	}
	else{
		*return_value = NULL;
	}
}

void Vector::Set( unsigned int i, VECTOR_TYPE value ){
	if( i < this->size ){
		this->data[ i ] = value;
	}
}

bool Vector::Add( Vector v ){
	if( this->size == v.size ){
		for( unsigned int i = 0; i < this->size; i += 1 ){
			data[ i ] += v.data[ i ];
		}
		return true;
	}
	return false;
}

VECTOR_TYPE Vector::ScalarProduct( Vector v ){
	VECTOR_TYPE result = 0.0;
	if( v.size == this->size ){
		for( unsigned int i = 0; i < this->size; i++ ){
			result += (this->data[ i ] * v.data[ i ]);
		}
	}
	return result;
}

void Vector::Scale( double r ){
	for( unsigned int i = 0; i < this->size; i++ ){
		this->data[ i ] = (double)this->data[ i ] * r;
	}
}

double Vector::Lenght(){
	double result_squared = this->ScalarProduct( *this );
	return sqrt( result_squared );
}

bool Vector::Equals( Vector v ){
	bool isEqual = false;
	if( this->size == v.size ){
		bool isEqual = true;
		unsigned int i = 0;
		while( i < this->size && isEqual ){
			if( this->data[ i ] != v.data[ i ] ){
				isEqual = false;
			}
			i++;
		}
	}
	return isEqual;
}