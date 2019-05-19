#include "ColoredBitmap.hpp"

ColoredBitmap::ColoredBitmap( unsigned int _rows, unsigned int _columns, int color ) : Bitmap( _rows, _columns ){
	this->color = color;
}