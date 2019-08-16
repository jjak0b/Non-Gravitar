#pragma once

#include "Bitmap.hpp"
#include <string>

class PrintableBitmap : public Bitmap{
protected:
	std::string* buffer;
public:
	PrintableBitmap( unsigned int _rows = 0, unsigned int _columns = 0);

	virtual ~PrintableBitmap();

	const char* toString();
};