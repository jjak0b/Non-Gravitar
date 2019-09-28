#include <cmath>
#include <stddef.h>
#include "Vector.hpp"

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

Vector Vector::Add( Vector v ){
	unsigned int _size = this->size < v.size ? this->size : v.size;
	for( unsigned int i = 0; i < _size; i += 1 ){
		this->data[ i ] += v.data[ i ];
	}
	return *this;
}

VECTOR_VALUE_TYPE Vector::ScalarProduct( Vector v ){
	VECTOR_VALUE_TYPE result = 0.0;
	if( v.size == this->size ){
		for( unsigned int i = 0; i < this->size; i++ ){
			result += (this->data[ i ] * v.data[ i ]);
		}
	}
	return result;
}

Vector Vector::Scale( double r ){
	for( unsigned int i = 0; i < this->size; i++ ){
		this->data[ i ] = this->data[ i ] * r;
	}
	return *this;
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

bool GetUnitOffset( VECTOR_VALUE_TYPE* offset, const VECTOR_VALUE_TYPE start, const VECTOR_VALUE_TYPE end, const unsigned int index_dimension, Vector* bounds ){
	VECTOR_VALUE_TYPE bound_value = 0;
	if( offset != NULL && bounds != NULL && bounds->Get(index_dimension, &bound_value ) ){
		*offset = end - start;
		if( bounds != NULL && bounds->Get(index_dimension, &bound_value ) ){
			if( *offset > 0 && *offset > (bound_value / 2.0 ) ){
				*offset = bound_value - *offset;
			}
			else if( *offset < 0 && (-(*offset)) > (bound_value / 2.0 ) ){
				*offset = -bound_value - *offset;
			}
			return true;
		}
	}
	return false;
}

bool GetOffSet( VECTOR_VALUE_TYPE* offset, Vector start, Vector end, const unsigned int index_dimension, Vector* bounds ){
	VECTOR_VALUE_TYPE valueEnd = 0, valueStart = 0, bound_value = 0;
	if( start.GetSize() == end.GetSize() && offset != NULL ){
		if( end.Get( index_dimension, &valueEnd) && start.Get( index_dimension, &valueStart) ){
			return GetUnitOffset( offset, valueStart, valueEnd, index_dimension, bounds );
		}
	}
	return false;
}

Vector BuildDirection( Vector start, Vector end, Vector* bounds ){
	Vector direction = Vector( start.GetSize() );
	VECTOR_VALUE_TYPE value = 0;
	if( start.GetSize() == end.GetSize() ){
		for( unsigned int i = 0; i < direction.GetSize(); i++ ){
			if( GetOffSet( &value, start, end, i, bounds ) ){
				direction.Set( i , value );
			}
		}
	}
	return direction;
}