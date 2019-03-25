#include "Viewport.hpp"
#include "Entity.hpp"
#include "ColoredBitmap.hpp"
#include "Level.hpp"
#include <iostream>

ViewPort::ViewPort( unsigned int _width, unsigned int _height, Point2D origin ){
	this->data = NULL;
	this->world_origin = origin;
	this->UpdateSize( width, _height );
}

void ViewPort::UpdateSize( unsigned int _width, unsigned int _height ){
	if( _width != this->GetWidth() || _height != this->height ){
		this->width = _width;
		this->height = _height * 2; // poichè usiamo il terminale, considero virtualmente il doppio dell'altezza perchè così posso lavorare sui caratteri "pixel"
		this->Dispose();
		this->data = new PrintableBitmap( _height, _width );
	}
}

void ViewPort::Draw( Bitmap *texture, Level *world, Point2D world_point ){
	if( this->data != NULL){
		Point2D point_relative_to_center_view = ViewPort::WorldPointToViewPoint( world, world_point );
		// correggo le coordinate relative alla view, per far si che la texture si centrata rispetto alla coordinata
		// ( cioè per partire a copiare da in alto a sinistra;
		// ovvero da x-texture->GetColumns()/2 e y+texture->GetRows()/2 )
		point_relative_to_center_view.x -= texture->GetColumns()/2;
		point_relative_to_center_view.y += texture->GetRows()/2;
		Point2D point_on_bitmap = ViewPointToBitMapPoint( point_relative_to_center_view, this->data );
		data->Copy( texture, point_on_bitmap.y, point_on_bitmap.x );
	}
}

BITMAP_DATA_TYPE ViewPort::GetBitmapData( Point2D view_point ){
	Point2D bitmapPoint = ViewPointToBitMapPoint( view_point, this->data );
	if( this->data != NULL ){
		return this->data->GetValue( bitmapPoint.y, bitmapPoint.x );
	}
	return BITMAP_DATA_NULL;
}

bool ViewPort::SetBitmapData( BITMAP_DATA_TYPE value, Point2D view_point ){
	Point2D bitmap_point = ViewPointToBitMapPoint( view_point, this->data );
	if( this->data != NULL ){
		return this->data->SetValue( value, bitmap_point.y, bitmap_point.x );
	}
	return false; 
}

bool ViewPort::SetPixel( Point2D view_point ){
	BITMAP_DATA_TYPE value;
	BITMAP_DATA_TYPE current_pixel = this->GetBitmapData( view_point );
	bool b_isPixelDown = false;

	if( ( view_point.y % 2 == 0 ) ){
		b_isPixelDown = true;
	}

	if ( current_pixel == CHAR_PIXEL_UP ) {
		if( b_isPixelDown ){
			value = CHAR_PIXEL_UP_DOWN;
		}
		else{
			value = CHAR_PIXEL_UP;
		}
	}
	else if( current_pixel == CHAR_PIXEL_DOWN ){
		if( b_isPixelDown ){
			value = CHAR_PIXEL_DOWN;
		}
		else{
			value = CHAR_PIXEL_UP_DOWN;
		}
	}
	else{
		if( b_isPixelDown ){
			value = CHAR_PIXEL_DOWN;
		}
		else{
			value = CHAR_PIXEL_UP;
		}
	}
	return this->SetBitmapData( value, view_point );
}

void ViewPort::Refresh(){
	if( this->data != NULL )
		std::cout << this->data->toString();
}

Point2D ViewPointToBitMapPoint( Point2D view_point, Bitmap *bitmap ){
	unsigned int y = 0;
	if( ( view_point.y % 2 == 1 ) ){
		y = ( bitmap->GetRows()-1 ) - (view_point.y-1); // quando la coordinata è dispari, considero la riga successiva
	}
	else{
		y = ( bitmap->GetRows()-1 ) - (view_point.y);
	}
	return Point2D( view_point.x, y );
}

Point2D ViewPort::WorldPointToViewPoint( Level *world, Point2D world_point ){
	return Point2D( ( (this->width/2) + ( world_point.x - this->world_origin.x ) ) % world->GetMaxWidth(),
					( (this->height/2) + ( world_point.y - this->world_origin.y ) ) % world->GetMaxHeight() );
}

void ViewPort::Dispose(){
	if( this->data != NULL ){
		this->data->Dispose();
		delete this->data;
	}
}