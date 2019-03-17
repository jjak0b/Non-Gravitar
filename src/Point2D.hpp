#pragma once

class Point2D{
	public:
	int x, y;

	Point2D( int _x = 0, int _y = 0 );
	int Distance( Point2D p );
};