#include "Line2D.hpp"
#include <stddef.h>

Line2D::Line2D( Side segment, Vector* bounds ): Side( segment.GetStart(), segment.GetEnd() ){
	evaluate( bounds );
}

void Line2D::evaluate(Vector* bounds ){
	VECTOR_VALUE_TYPE difference_x, difference_y, temp;
	GetOffSet( &difference_x, start, end, 0, bounds );
	GetOffSet( &difference_y, start, end, 1, NULL );

	isVertical = true;
	if ( difference_x != 0 ) {
		m = difference_y / difference_x ;
		GetUnitOffset(&q, m * start.GetX(), start.GetX(), 1, NULL ); // y - fx()
		isVertical = false;
	}
}

bool Line2D::GetM( VECTOR_VALUE_TYPE* value ){
	if( isVertical ){
		return false;
	}
	else{
		*value = m;
		return true;
	}
}

/**
 * @brief restituisce il valore dell'ordinata all'origine, assegnandolo a value
 * @PreCondition: value != NULL, bounds != NULL
 * @param value 
 * @param bounds : Limiti degli assi
 * @return true se a value è stato assegnato un valore -> la retta non è verticale
 * @return false altrimenti -> M è nullo quindi la retta à verticale
 */
bool Line2D::GetQ( VECTOR_VALUE_TYPE* value ){
	if( isVertical ){
		return false;
	}
	else{
		*value = q;
		return true;
	}
}

/**
 * @brief Indica se la retta è verticale in base al suo coefficiente angolare
 * 
 * @return true 
 * @return false 
 */
bool Line2D::IsVertical(){
	return isVertical;
}

/**
 * @brief Indica se questa retta infinita interseca la retta infinita line
 * 
 * @param line 
 * @return true 
 * @return false 
 */
bool Line2D::IsIntersecting( Line2D line ){

	if( this->isVertical && line.isVertical ){
		if( this->start.GetX() == line.start.GetX() ){ // rette coincidenti
			return true;
		}
		else{ // rette parallele
			return false;
		}
	}
	else if( this->isVertical || line.isVertical ){
		return true;
	}
	else if( this->m == line.m ){ // rete paralle
		return false;
	}
	else{
		return true;
	}
}