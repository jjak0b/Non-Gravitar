#pragma once

#include "Bitmap.hpp"
#include "Color.hpp"

class ColoredBitmap : public Bitmap{
public:
	ColoredBitmap( unsigned int _rows = 0, unsigned int _columns = 0, Color color = COLOR_WHITE );

	unsigned int GetColumns();

	void SetSignificantColumns( unsigned int _columns );

	bool SetColor( Color color, unsigned int _row, unsigned int _column );

	Color GetColor( unsigned int _row, unsigned int _column );

	bool SetValue( BITMAP_DATA_TYPE value, unsigned int row, unsigned int column );

	BITMAP_DATA_TYPE GetValue( unsigned int row, unsigned int column );

	bool Load( const BITMAP_DATA_TYPE **texture, const Color **color_table, unsigned int _rows, unsigned int _columns );

	void Copy( ColoredBitmap *_data, unsigned int row, unsigned int column );

	void Clear();
};