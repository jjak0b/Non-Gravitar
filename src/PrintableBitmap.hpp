#pragma once

#include "Bitmap.hpp"

class PrintableBitmap : public Bitmap{
public:
	PrintableBitmap( unsigned int _rows = 0, unsigned int _columns = 0);

	char* toString();
};