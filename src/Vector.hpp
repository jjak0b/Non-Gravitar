#pragma once

#define VECTOR_TYPE int

class Vector{
private:
	VECTOR_TYPE *data; // puntatore dell'array contenente le componenti del vettore
protected:
	unsigned int size; // dimensione vettore
public:
	Vector( unsigned int _size = 1 );

	/**
	 * @brief Restituisce la dimensione del vettore
	 * @return unsigned int 
	 */
	unsigned int GetSize();

	/**
	 * @brief assegna il valore dell'i-esima componente al puntatore return_value
	 * PostCondition: a return_value viene assegnato il valore della i-esima componente del vettore, 
	 * se i < GetSize() sarà assegnato il valore NULL
	 * @param i 
	 * @param return_value : indirizzo in cui verrà memorizzato il valore da restituire
	 */
	void Get( unsigned int i, VECTOR_TYPE *return_value );

	/**
	 * @brief Assegna il valore indicato alla i-esima componente del vettore
	 * @param i
	 * @param value 
	 */
	void Set( unsigned int i, VECTOR_TYPE value );

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
	VECTOR_TYPE ScalarProduct( Vector v );

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
	 * @brief Verifica se le componenti di v sono uguali a quelle di questo oggetto chiamante
	 * @param v : Vettore da confrontare
	 * @return true se c[i] == c[i] per i < GetSize() ( dove c è la componente )
	 * @return false altrimenti
	 */
	bool Equals( Vector v );
};