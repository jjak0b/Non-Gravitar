// #pragma once


#ifndef INCLUDE_BITMAP_HPP
#define INCLUDE_BITMAP_HPP

typedef char BITMAP_DATA_TYPE;
#define BITMAP_DATA_EMPTY ' '
#define BITMAP_DATA_NULL '\0'

#include "shared/Matrix.hpp"
#include "shared/Color.hpp"

class Bitmap : public Matrix::Matrix< BITMAP_DATA_TYPE > {
protected:
	Matrix<Color>* colors;
public:
	Bitmap( unsigned int _rows = 0, unsigned int _columns = 0, Color color = COLOR_TRANSPARENT );

	virtual ~Bitmap();

	bool SetColor( Color color, unsigned int _row, unsigned int _column );

	Color GetColor( unsigned int _row, unsigned int _column );


	BITMAP_DATA_TYPE GetValue( unsigned int row, unsigned int column );

	bool Load( const BITMAP_DATA_TYPE **texture, const Color **color_table, unsigned int _rows, unsigned int _columns );

	void Copy( Bitmap *_data, unsigned int row, unsigned int column );

	void Clear();
};

#endif