#pragma once

#include "Bitmap.hpp"


class ColoredBitmap : public Bitmap{
protected:
	int color;
public:
	ColoredBitmap( unsigned int _rows = 0, unsigned int _columns = 0, int color = 0 );

	int GetColor();
	void SetColor();
};