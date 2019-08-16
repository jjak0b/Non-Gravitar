#pragma once

#include "Vector.hpp"

class Point : public Vector{
public:
	Point( unsigned int size = VECTOR_DIMENSIONS );

	/**
	 * @brief Effettua la distanza quadratica euclidea tra questo punto e P;
	 * inoltre se le coordinate sono cicliche, è possibile ottenere la distanza quadratica in base ai limiti nelle dimensioni di bounds
	 * restituisce -1 se i punti hanno dimensioni diverse
	 * es: (1,0).DistanceSquared( ( 89, 0 ), NULL ) = 88^2;
	 * es: (1,0).DistanceSquared( ( 89, 0 ), ( 90, 0 ) ) = 2^2;
	 * PreCondition: p.GetSize() == GetSize(), bounds = NULL se non vi è presente alcun limite;
	 * @param p 
	 * @param bounds 
	 * @return VECTOR_VALUE_TYPE 
	 */
	VECTOR_VALUE_TYPE DistanceSquared( Point p, Vector* bounds );

	/**
	 * @brief Effettua la distanza euclidea tra questo punto e P;
	 * inoltre se le coordinate sono cicliche, è possibile ottenere la distanza in base ai limiti nelle dimensioni di bounds
	 * es: (1,0).Distance( ( 89, 0 ), NULL ) = 88;
	 * es: (1,0).Distance( ( 89, 0 ), ( 90, 0 ) ) = 2;
	 * restituisce -1 se i punti hanno dimensioni diverse
	 * PreCondition: p.GetSize() == GetSize(), bounds = NULL se non vi è presente alcun limite;
	 * @param p 
	 * @param bounds 
	 * @return VECTOR_VALUE_TYPE 
	 */
	VECTOR_VALUE_TYPE Distance( Point p, Vector* bounds );
};
