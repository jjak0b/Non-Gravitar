#include "Viewport.hpp"
#include "Entity.hpp"
#include "ColoredBitmap.hpp"
#include "Level.hpp"
#include "GameConfig.h"
#include <iostream>
#include <cmath>
#include <cstring>

ViewPort::ViewPort( unsigned int _width, unsigned int _height, Point2D origin ){
	this->data = NULL;
	this->width = 1;
	this->height = 1;
	this->world_origin = origin;
	this->UpdateSize( _width, _height );
}

ViewPort::~ViewPort(){
	this->Dispose();
}

bool ViewPort::UpdateSize( unsigned int _width, unsigned int _height ){
	_width = _width > 0 ? _width : 1;
	_height = _height > 2 ? _height : 2;
	if( _width != this->width || _height * 2 != this->height ){
		this->width = _width;
		this->height = _height * 2; // poichè usiamo il terminale, considero virtualmente il doppio dell'altezza perchè così posso lavorare sui caratteri "pixel"
		this->Dispose();
		this->data = new PrintableBitmap( _height, _width );
		return true;
	}
	return false;
}

void ViewPort::Draw( ColoredBitmap *texture, Level *world, Point2D world_point ){
	if( this->data != NULL){
		Point2D point_relative_to_bottom_left_view = this->WorldPointToViewPoint( world, world_point );
		// ovvero da x-texture->GetColumns()/2 e y+texture->GetRows()/2 )
		// point_relative_to_center_view.x -= texture->GetColumns()/2;
		// point_relative_to_center_view.y += texture->GetRows()/2;

		if( texture != NULL ){ // Jacopo TODO: da sistemare
			Point2D point_on_bitmap = ViewPointToBitMapPoint( point_relative_to_bottom_left_view, this->data );
			// correggo le coordinate relative alla view, per far si che la texture sia centrata rispetto alla coordinata
			// ( cioè per partire a copiare da in alto a sinistra;
			Vector offset_from_bitmap_point_to_texture_top_left = Vector( point_on_bitmap.GetSize() );
			offset_from_bitmap_point_to_texture_top_left.Set( 0, -(int)(texture->GetColumns()/2.0) );
			offset_from_bitmap_point_to_texture_top_left.Set( 1, 1 - (int)(texture->GetRows()) ); // l'1 è riferito alla riga "extra" della viewport che contiene 2 caratteri
			point_on_bitmap.Add( offset_from_bitmap_point_to_texture_top_left );

			data->Copy( texture, point_on_bitmap.GetY(), point_on_bitmap.GetX() );
			this->SetPixel( point_relative_to_bottom_left_view, COLOR_WHITE );
		}
		else{
			this->SetPixel( point_relative_to_bottom_left_view, COLOR_WHITE );
		}
	}
}

void ViewPort::Print( const char str_text[], Point2D view_point, Color color ){

	view_point.round();
	// se il punto è fuori dal range della viewport termina la funzione
	if( view_point.GetX() < 0 || view_point.GetX() >= this->GetWidth() || view_point.GetY() < 0 || view_point.GetY() >= this->GetHeight() ){
		return;
	}

	// se la coordinata dell'ordinata è dispari, il carattere non può essere stampato nel pixel superiore, quindi sarà stampato nel pixel inferiore
	if( (int)view_point.GetY() % 2 == 1 ){
		view_point.SetY( view_point.GetY() - 1 );
	}

	int length = strlen( str_text );
	Point2D point_cursor = view_point;
	int i = 0;
	BITMAP_DATA_TYPE value = '\0';

	while( i < length ){
		value = str_text[i];
		// Rimandare la lettera attuale al ciclo successivo, per cambiare in questo il cursore alla riga successiva
		// Se view_point risulata essere alla coordinata precedente a this->GetWidth(), la stringa risulterà essere verticale
		if( point_cursor.GetX() >= this->GetWidth() ){ 
			value = '\n';
			i -= 1;
		}

		if( value == '\n' ){
			int offset_y = -1;
			point_cursor.SetX( view_point.GetX() );
			// nella coordinata dell'ordinata dispari, equivale al mezzo-carattere sopra;
			// quindi scendo ancora di 2 così arrivo ad una riga nuova della bitmap
			if( (int)point_cursor.GetY() % 2 == 1 ){
				offset_y = -2;
			}
			point_cursor.SetY( point_cursor.GetY() + offset_y );
			point_cursor.SetX( view_point.GetX() );
			
		}
		else{
			this->SetBitmapData( value, color, point_cursor );
			point_cursor.SetX( point_cursor.GetX() + 1 );
		}
		
		i += 1;
	}
}

BITMAP_DATA_TYPE ViewPort::GetBitmapData( Point2D view_point ){
	Point2D bitmapPoint = ViewPointToBitMapPoint( view_point, this->data );
	bitmapPoint.round();
	if( this->data != NULL ){
		return this->data->GetValue( bitmapPoint.GetY(), bitmapPoint.GetX() );
	}
	return BITMAP_DATA_NULL;
}

bool ViewPort::SetBitmapData( BITMAP_DATA_TYPE value, Color color, Point2D view_point ){
	Point2D bitmap_point = ViewPointToBitMapPoint( view_point, this->data );
	bitmap_point.round();
	if( this->data != NULL ){
		if( IS_PIXEL_DATA( value ) ){
			return this->SetPixel( view_point, color );
		}
		else{
			return this->data->SetValue( value, bitmap_point.GetY(), bitmap_point.GetX() );
		}
	}
	return false; 
}

bool ViewPort::SetPixel( Point2D view_point, Color color ){
	view_point.round();
	BITMAP_DATA_TYPE value = BITMAP_DATA_NULL;
	BITMAP_DATA_TYPE current_pixel = this->GetBitmapData( view_point );
	bool b_isPixelDown = false;

	if( ( (int)view_point.GetY() % 2 == 0 ) ){
		b_isPixelDown = true;
	}

	if ( current_pixel == CHAR_PIXEL_UP ) {
		if( b_isPixelDown ){
			value = CHAR_PIXEL_UP_DOWN;
		}
	}
	else if( current_pixel == CHAR_PIXEL_DOWN ){
		if( !b_isPixelDown ){
			value = CHAR_PIXEL_UP_DOWN;
		}
	}
	else if( current_pixel == CHAR_PIXEL_EMPTY ){
		if( b_isPixelDown ){
			value = CHAR_PIXEL_DOWN;
		}
		else{
			value = CHAR_PIXEL_UP;
		}
	}

	if( value != BITMAP_DATA_NULL ){
		Point2D bitmap_point = ViewPointToBitMapPoint( view_point, this->data );
		bitmap_point.round();
		this->data->SetColor( color, bitmap_point.GetY(), bitmap_point.GetX() );
		return this->data->SetValue( value, bitmap_point.GetY(), bitmap_point.GetX() );
	}
	return false;
}

void ViewPort::Clear(){
	this->data->Clear();
}

void ViewPort::Refresh(){
	if( this->data != NULL )
		std::cout << this->data->toString();
}


Point2D ViewPointToBitMapPoint( Point2D view_point, ColoredBitmap *bitmap ){
	if( bitmap == NULL ){
		return Point2D( 0, 0 );
	}
	view_point.round();
	unsigned int y = 0;
	int offset_y = (bitmap->GetRows()*2) - 1;
	if( ( (int)view_point.GetY() % 2 == 1 ) ){
		y =  offset_y - (view_point.GetY()-1); // quando la coordinata è dispari, considero la riga successiva
	}
	else{
		y =  offset_y - (view_point.GetY());
	}
	y = y /2;
	return Point2D( view_point.GetX(), y );
}

Point2D ViewPort::WorldPointToViewPoint( Level *world, Point2D world_point ){

	// return Point2D( ( (this->width/2) + ( world_point.x - this->world_origin.x ) ) % world->GetMaxWidth(), ( (this->height/2) + ( world_point.y - this->world_origin.y ) ) % world->GetMaxHeight() );
	VECTOR_VALUE_TYPE x = (world->GetMaxWidth() - this->world_origin.GetX() + world_point.GetX());
	VECTOR_VALUE_TYPE y = (world->GetMaxHeight() - this->world_origin.GetY() + world_point.GetY());
	int int_point_value_x = (int)x;
	int int_point_value_y = (int)y;
	x = int_point_value_x % world->GetMaxWidth() + ( x - int_point_value_x );
	y = int_point_value_y % world->GetMaxHeight() + ( y - int_point_value_y );
	Point2D viewPoint = Point2D( x, y );
	viewPoint.round();
	return viewPoint;
}

void ViewPort::Dispose(){
	if( this->data != NULL ){
		delete this->data;
		this->data = NULL;
	}
}

unsigned int ViewPort::GetWidth(){
	return this->width;
}

unsigned int ViewPort::GetHeight(){
	return this->height;
}

void ViewPort::SetWorldOrigin( Point2D WorldOrigin ){
	this->world_origin = WorldOrigin;
}

void DrawLine( ViewPort *view, Level *world, Point2D start, Point2D end, Color color ){
	bool isVertical = false; // la retta è verticale
	double angular_coeffcient = 0.0; // coeff. angolare della retta
	if( end.GetX() - start.GetX() != 0){
		angular_coeffcient = (end.GetY() - start.GetY()) / ( end.GetX() - start.GetX() );
	}
	else{ // il coeff angolare non è definito per tan( 90° )
		isVertical = true;
	}

	Point2D temp_point = Point2D();
	VECTOR_VALUE_TYPE
		x, y,
		inc_value = 1.0f, // rateo di campionatura
		distance = 0.0f,
		distance_x = abs( end.GetX() - start.GetX()),
		distance_y = abs( end.GetY() - start.GetY());

	if( isVertical ){
		distance = distance_y;
	}
	else{
		distance = distance_x;

		// se si trova nella stessa ordinata, la campionatura basta di 1 unità
		// altrimenti la risoluzione di campionamento delle ascisse diventa sempre più precisa quando la retta tende ad essere verticale
		if( distance_y != 0 ){
			inc_value = min( 1.0f, distance_x / distance_y );
		}
	}

	for( VECTOR_VALUE_TYPE i = 0.0; i < distance; i += inc_value ){
		if( isVertical ){
			x = 0.0;
			if( end.GetY() >= start.GetY() ){
				y = i;
			}
			else{
				y = -i;
			}
		}
		else{
			if( end.GetX() >= start.GetX() ){
				x = i;
			}
			else{
				x = -i;
			}
			y = x * angular_coeffcient;
		}
		temp_point.SetX( x );
		temp_point.SetY( y );
		temp_point.Add( start );
		view->SetPixel( view->WorldPointToViewPoint( world, temp_point ), color );
	}
	view->SetPixel( view->WorldPointToViewPoint( world, end ), color );
}

void DrawCircle( ViewPort *view, Level *world, Point2D world_origin, double radius, Color color ){
	Point2D circle_point;
	double tmp_x = 0, tmp_y = 0;
	const double DEGREESTEP = 5;
	const double DEGREES = 360.0;
	const double DEG_TO_RAD_COEF = (M_PI / 180.0);
	double rad = 0.0;
	
	for (double deg = 0.0; deg < DEGREES; deg += DEGREESTEP ){
		rad = deg * DEG_TO_RAD_COEF;
		tmp_y = radius * sin( rad );
		tmp_x = radius * cos( rad );
		
		circle_point.SetX( tmp_x );
		circle_point.SetY( tmp_y );
		circle_point.Add( world_origin );
		view->SetPixel( view->WorldPointToViewPoint( world, circle_point), color );
	}
}