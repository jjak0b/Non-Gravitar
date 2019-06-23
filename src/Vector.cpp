#include "Vector.hpp"
#include <stddef.h>
#include <cmath>

Vector::Vector( unsigned int _size ){
	if( _size > VECTOR_DIMENSIONS ){
		_size = VECTOR_DIMENSIONS;
	}
	this->size = _size;
	if( _size > 0 ){
		this->Reset();
	}
}

Vector Vector::Duplicate(){
	Vector v = Vector( this->size );
	v.Add( *this );
	return v;
}

unsigned int Vector::GetSize(){
	return this->size;
}

bool Vector::Get( unsigned int i, VECTOR_VALUE_TYPE *return_value ){
	if( i < this->size && return_value != NULL ){
		*return_value = this->data[ i ];
		return true;
	}
	return false;
}

bool Vector::Set( unsigned int i, VECTOR_VALUE_TYPE value ){
	if( i < this->size ){
		this->data[ i ] = value;
		return true;
	}
	return false;
}

void Vector::Reset(){
	for( unsigned int i = 0; i < this->size; i += 1 ){
		this->data[ i ] = 0.0;
	}
}

bool Vector::Add( Vector v ){
	if( this->size == v.size ){
		for( unsigned int i = 0; i < this->size; i += 1 ){
			this->data[ i ] += v.data[ i ];
		}
		return true;
	}
	return false;
}

VECTOR_VALUE_TYPE Vector::ScalarProduct( Vector v ){
	VECTOR_VALUE_TYPE result = 0.0;
	if( v.size == this->size ){
		for( unsigned int i = 0; i < this->size; i++ ){
#if (VECTOR_VALUE_TYPE == int)
			result += std::round(this->data[ i ] * v.data[ i ]);
#else
			result += (this->data[ i ] * v.data[ i ]);
#endif
		}
	}
	return result;
}

void Vector::Scale( double r ){
	for( unsigned int i = 0; i < this->size; i++ ){
#if (VECTOR_VALUE_TYPE == int)
		this->data[ i ] = std::round( (double)this->data[ i ] * r );
#else
		this->data[ i ] = this->data[ i ] * r;
#endif
	}
}

double Vector::Lenght(){
	double result_squared = this->ScalarProduct( *this );
	return sqrt( result_squared );
}

void Vector::Normalize(){
	double v_lenght = this->Lenght();
	if( v_lenght != 0.0 ){
		this->Scale( 1.0 / v_lenght );
	}
}

bool Vector::Equals( Vector v ){
	bool isEqual = this->size == v.size;
	if( isEqual ){
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

bool Vector::IsNull(){
	bool isNull = true;
	int i = 0;
	while( isNull && i < this->size ){
		if( this->data[ i ] != 0 ){
			isNull = false;
		}
		i++;
	}
	return isNull;
}

void Vector::round(){
	for( unsigned int i = 0; i < this->size; i++){
		this->data[ i ] = std::round( this->data[ i ] );
	}
}