#pragma once

#include "Point2D.hpp"
#include "Bitmap.hpp"
#include "PrintableBitmap.hpp"

#define CHAR_PIXEL_EMPTY ((char)32)
#define CHAR_PIXEL_UP ((char)223)
#define CHAR_PIXEL_DOWN ((char)220)
#define CHAR_PIXEL_UP_DOWN ((char)219)

class Level;

class ViewPort{
protected:
	Point2D world_origin;
	unsigned int width = 0, height = 0;
	PrintableBitmap *data;
public:
	ViewPort( unsigned int width, unsigned int height, Point2D origin );
	void Dispose(); // libera le risorse di data
	void Draw( Bitmap *texture, Level *level, Point2D world_origin );
	void Clear();
	void Refresh();
	void UpdateSize( unsigned int width, unsigned int height );

	/**
	 * @brief Stampa del testo sulla Schermata di gioco ("simula una specie di HUD") in uno specifico punto
	 * 
	 * @param str_text 
	 * @param view_point punto da dove iniziare a stampare
	 */
	void Print( char *str_text, Point2D view_point );

	BITMAP_DATA_TYPE GetBitmapData( Point2D view_point );

	bool SetBitmapData( BITMAP_DATA_TYPE value, Point2D view_point );

	bool SetPixel( Point2D view_point );

	Point2D WorldPointToViewPoint( Level *world, Point2D world_point );

	unsigned int GetWidth();

	unsigned int GetHeight();

	void SetWorldOrigin( Point2D WorldOrigin );
};

/**
 * @brief Converte le coordinate locali relative alla viewport nelle corrispondenti relative alla bitmap specificata
 * @param view_point 
 * @param bitmap 
 * @return Point2D 
 */
Point2D ViewPointToBitMapPoint( Point2D view_point, Bitmap *bitmap );

/**
 * @brief Disegna nella ViewPort un linea a partire da start fino a end, dove start e end sono coordinate del mondo
 * @param view 
 * @param world 
 * @param start 
 * @param end 
 */
void DrawLine( ViewPort *view, Level *world, Point2D start, Point2D end );