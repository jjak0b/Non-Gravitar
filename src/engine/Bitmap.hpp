// #pragma once


#ifndef INCLUDE_BITMAP_HPP
#define INCLUDE_BITMAP_HPP

typedef char BITMAP_DATA_TYPE;
#define BITMAP_DATA_EMPTY ' '
#define BITMAP_DATA_NULL '\0'

#include "shared/Matrix.hpp"
#include "shared/Color.hpp"
/**
 * @brief La classe rappresentante un immagine.
 * è una matrice di caratteri simulante un insieme di Pixel aventi uno stesso colore
 * e una matrice di colori
 * ad ogni carattere è associato il suo colore nella stessa posizionee
 */
class Bitmap : public Matrix::Matrix< BITMAP_DATA_TYPE > {
protected:
	Matrix<Color>* colors;
public:
	/**
	 * @brief costruttore di un oggetto Bitmap avente le dimensioni specificate, e con lo stesso colore impostato
	 * 
	 * @param _rows
	 * @param _columns
	 * @param color
	 */
	Bitmap( unsigned int _rows = 0, unsigned int _columns = 0, Color color = COLOR_TRANSPARENT );

	virtual ~Bitmap();

	/**
	 * @brief Imposta il colore alla posizione specificata
	 * 
	 * @param color 
	 * @param _row 
	 * @param _column 
	 * @return true se è il colore è stato inserito alla posizione indicata
	 * @return false altrimenti, ovvero quando è fornita una posizione non valida
	 */
	bool SetColor( Color color, unsigned int _row, unsigned int _column );

	/**
	 * @brief Restituisce il colore alla posizione fornita
	 * @PostCondition: resituisce COLOR_TRANSPARENT in caso di posizione non valida
	 * (anche se tale colore può essere comunque assegnato ad una qualsiasi posizione)
	 * @param _row
	 * @param _column 
	 * @return Color 
	 */
	Color GetColor( unsigned int _row, unsigned int _column );

	/**
	 * @brief Restituisce il valore del carattere alla posizione indicata
	 * @PostCondition: Restituisce BITMAP_DATA_NULL in caso di poszione non valida
	 * @param row 
	 * @param column 
	 * @return BITMAP_DATA_TYPE 
	 */
	BITMAP_DATA_TYPE GetValue( unsigned int row, unsigned int column );

	/**
	 * @brief Carica in questo oggetto una matrice di caratteri e una di colori.
	 * Vedere Matrix::Load
	 * @PreCondition: Le dimensioni delle due matrici devono essere uguali,
	 * poichè ad un unico carattere deve corrispondere un colore
	 * @param texture
	 * @param color_table 
	 * @param _rows
	 * @param _columns 
	 * @return true sia se il load sulla matrice dei caratteri che dei colori è avvenuto correttmente
	 * @return false 
	 */
	bool Load( const BITMAP_DATA_TYPE **texture, const Color **color_table, unsigned int _rows, unsigned int _columns );

	/**
	 * @brief Effettua la copia dell oggetto fornito inserendolo a partire dalla poszione fornita
	 * Vedere eventualmente Matrix::Copy
	 * In caso di posizione i,j + ( row, colum)-esima non valida, tale viene ignorata
	 * @param _data 
	 * @param row 
	 * @param column 
	 */
	void Copy( Bitmap *_data, unsigned int row, unsigned int column );

	/*
	 * @brief "Svuota" tutte le matrici assegnando a tutti gli elementi:
	 * BITMAP_DATA_EMPTY a quella dei caratteri
	 * COLOR_TRANSPARENT a quella dei colori
	 */
	void Clear();
};

#endif