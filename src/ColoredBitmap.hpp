#pragma once

#include "Bitmap.hpp"


class ColoredBitmap : public Bitmap{
protected:
	int color;
public:
	ColoredBitmap( unsigned int _rows, unsigned int _columns, int color );

	int GetColor();
	void SetColor();
};