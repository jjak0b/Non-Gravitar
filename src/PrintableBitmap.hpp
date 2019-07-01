#pragma once

#include "ColoredBitmap.hpp"

class PrintableBitmap : public ColoredBitmap{
public:
	PrintableBitmap( unsigned int _rows = 0, unsigned int _columns = 0);

	char* toString();
};