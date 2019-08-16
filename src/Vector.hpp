#pragma once

#define VECTOR_VALUE_TYPE float // tipo delle singole componenti di un vettore
// NOTA: definire VECTOR_DIMENSION prima di includere questo header per sovrascrivere
#ifndef VECTOR_DIMENSIONS
#define VECTOR_DIMENSIONS 2 // dimensione vettore standard
#endif

class Vector{
protected:
	VECTOR_VALUE_TYPE data[ VECTOR_DIMENSIONS ]; // array contenente le componenti del vettore
	unsigned int size; // dimensione vettore
public:
	/**
	 * @brief Costruttore di un vettore aventi _size componenti
	 * PreCondition: _size deve essere <= VECTOR_DIMENSIONS
	 * @param int 
	 */
	Vector( unsigned int _size = VECTOR_DIMENSIONS );

	/**
	 * @brief Restituisce un copia di questo oggetto
	 * 
	 * @return Vector
	 */
	Vector Duplicate();
	
	/**
	 * @brief Restituisce la dimensione del vettore
	 * @return unsigned int 
	 */
	unsigned int GetSize();

	/**
	 * @brief assegna il valore dell'i-esima componente al puntatore return_value
	 * PostCondition: a return_value viene assegnato il valore della i-esima componente del vettore, 
	 * restituisce true se è stato assegnato un valore al valore puntato da return_value, false altrimenti
	 * @param i 
	 * @param return_value : indirizzo in cui verrà memorizzato il valore da restituire
	 * @return bool 
	 */
	bool Get( unsigned int i, VECTOR_VALUE_TYPE *return_value );

	/**
	 * @brief Assegna il valore indicato alla i-esima componente del vettore
	 * PostCondition: Restituisce true se è stato impostato il valore nell'indice specificato, false altrimenti
	 * @param i
	 * @param value 
	 * @return bool
	 */
	bool Set( unsigned int i, VECTOR_VALUE_TYPE value );
	
	/**
	 * @brief Assegna a tutte le componenti il valore 0
	 * 
	 */
	void Reset();

	/**
	 * @brief Somma tutte le componenti del vettore v alle componenti dell'oggetto da cui viene chiamata questa funzione
	 * @param v : Vettore da sommare a questo oggetto
	 * @return true se v.GetSize() == GetSize() e quindi viene effettuata la somma
	 * @return false se v.GetSize() != GetSize()
	 */
	bool Add( Vector v );

	/**
	 * @brief Considerando a questo vettore, effettua il prodotto scalare tra a e v
	 * PreCondition: a.GetSize() == v.getSize()
	 * @param v 
	 * @return int 
	 */
	VECTOR_VALUE_TYPE ScalarProduct( Vector v );

	/**
	 * @brief Effettua il prodotto per uno scalare r su questo vettore,
	 * poichè le componenti sono interi, il prodotto per scalare sarà troncato a intero
	 * @param r 
	 * @return Vector 
	 */
	void Scale( double r );

	/**
	 * @brief Effettua la norma euclidea sul vettore
	 * @return double 
	 */
	double Lenght();

	/**
	 * @brief Normalizza il vettore per far in modo che il vettore abbia lunghezza = 1
	 */
	void Normalize();

	/**
	 * @brief Verifica se le componenti di v sono uguali a quelle di questo oggetto chiamante
	 * @param v : Vettore da confrontare
	 * @return true se c[i] == c[i] per i < GetSize() ( dove c è la componente )
	 * @return false altrimenti
	 */
	bool Equals( Vector v );

	/**
	 * @brief Indica se il vettore è nullo, cioè tutte le componenti del vettore sono = 0
	 * @return true se è un vettore nullo
	 * @return false altrimenti 
	 */
	bool IsNull();

	/**
	 * @brief Approssima per eccesso o per difetto i valori delle componenti di questo oggetto
	 * 
	 */
	void round();
};

/**
 * @brief Restituisce true se è stato assegnato un valore al valore puntato da offset, false altrimenti
 * PreCondition: start, end, offset != NULL, start.GetSize() = end.GetSize()
 * PostCondition: Assegna il valore della differenza dell'i-esima componente di start e end al valore puntato da offset;
 * se bound != NULL allora tale valore viene ridimensionato in base al limite nella i-esima dimensione di bounds
 * 
 * es:
 * offset;
 * f( &offset, &(1,0), &(89,0), 0, &(90, 0) )
 * ->offset = 2
 * offset;
 * f( &offset, &(1,0), &(89,0), 0, NULL )
 * ->offset = 88
 * 
 * @param offset 
 * @param start 
 * @param end 
 * @param index_dimension 
 * @param bounds 
 * @return true se è stato assegnato un valore al valore puntato da offset
 * @return false altrimenti
 */
bool GetOffSet( VECTOR_VALUE_TYPE* offset, Vector start, Vector end, unsigned int i, Vector* bounds );

/**
 * @brief Restituisce il vettore direzione (offset) dal punto start a end (end-start);
 * inoltre se le direzioni sono cicliche, è possibile ottenere la direzione in base i limiti nelle dimensioni di bounds 
 * PreCondition: start.GetSize() == end.GetSize(), altrimenti verrà restituito un vettore con componenti nulle; bounds = NULL se non vi è presente alcun limite
 * @param start 
 * @param end 
 * @return Vector 
 */
Vector BuildDirection( Vector start, Vector end, Vector* bounds );