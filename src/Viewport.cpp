#include "Viewport.hpp"
#include "Entity.hpp"
#include "ColoredBitmap.hpp"
#include "Level.hpp"
#include <iostream>

ViewPort::ViewPort( unsigned int _width, unsigned int _height, Point2D origin ){
	this->data = NULL;
	this->width = 0;
	this->height = 0;
	this->world_origin = origin;
	this->UpdateSize( _width, _height );
}

void ViewPort::UpdateSize( unsigned int _width, unsigned int _height ){
	if( _width != this->width || _height * 2 != this->height ){
		this->width = _width;
		this->height = _height * 2; // poichè usiamo il terminale, considero virtualmente il doppio dell'altezza perchè così posso lavorare sui caratteri "pixel"
		this->Dispose();
		this->data = new PrintableBitmap( _height, _width );
	}
}

void ViewPort::Draw( Bitmap *texture, Level *world, Point2D world_point ){
	if( this->data != NULL){

		Point2D point_relative_to_bottom_left_view = this->WorldPointToViewPoint( world, world_point );
		// correggo le coordinate relative alla view, per far si che la texture si centrata rispetto alla coordinata
		// ( cioè per partire a copiare da in alto a sinistra;
		Point2D point_relative_to_center_view = point_relative_to_bottom_left_view;
		// ovvero da x-texture->GetColumns()/2 e y+texture->GetRows()/2 )
		// point_relative_to_center_view.x -= texture->GetColumns()/2;
		// point_relative_to_center_view.y += texture->GetRows()/2;

		if( texture != NULL ){ // Jacopo TODO: da sistemare
			Point2D point_on_bitmap = ViewPointToBitMapPoint( point_relative_to_center_view, this->data );
			data->Copy( texture, point_on_bitmap.GetY(), point_on_bitmap.GetX() );
		}
		else{
			this->SetPixel( point_relative_to_bottom_left_view );
		}
		
	}
}

BITMAP_DATA_TYPE ViewPort::GetBitmapData( Point2D view_point ){
	Point2D bitmapPoint = ViewPointToBitMapPoint( view_point, this->data );
	if( this->data != NULL ){
		return this->data->GetValue( bitmapPoint.GetY(), bitmapPoint.GetX() );
	}
	return BITMAP_DATA_NULL;
}

bool ViewPort::SetBitmapData( BITMAP_DATA_TYPE value, Point2D view_point ){
	Point2D bitmap_point = ViewPointToBitMapPoint( view_point, this->data );
	if( this->data != NULL ){
		return this->data->SetValue( value, bitmap_point.GetY(), bitmap_point.GetX() );
	}
	return false; 
}

bool ViewPort::SetPixel( Point2D view_point ){
	BITMAP_DATA_TYPE value;
	BITMAP_DATA_TYPE current_pixel = this->GetBitmapData( view_point );
	bool b_isPixelDown = false;

	if( ( view_point.GetY() % 2 == 0 ) ){
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

void ViewPort::Clear(){
	this->data->Clear();
}

void ViewPort::Refresh(){
	if( this->data != NULL )
		std::cout << this->data->toString();
}


Point2D ViewPointToBitMapPoint( Point2D view_point, Bitmap *bitmap ){
	unsigned int y = 0;
	int offset_y = (bitmap->GetRows()*2) - 1;
	if( ( view_point.GetY() % 2 == 1 ) ){
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
	return  Point2D( (world->GetMaxWidth() - this->world_origin.GetX() + world_point.GetX()) % world->GetMaxWidth(),
					 (world->GetMaxHeight() - this->world_origin.GetY() + world_point.GetY()) % world->GetMaxHeight() );
				
}

void ViewPort::Dispose(){
	if( this->data != NULL ){
		this->data->Dispose();
		delete this->data;
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