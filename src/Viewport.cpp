#include "Viewport.hpp"
#include "Entity.hpp"
#include "ColoredBitmap.hpp"
#include "Level.hpp"
#include <iostream>
#include <cmath>

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
		// ovvero da x-texture->GetColumns()/2 e y+texture->GetRows()/2 )
		// point_relative_to_center_view.x -= texture->GetColumns()/2;
		// point_relative_to_center_view.y += texture->GetRows()/2;

		if( texture != NULL ){ // Jacopo TODO: da sistemare
			Point2D point_on_bitmap = ViewPointToBitMapPoint( point_relative_to_bottom_left_view, this->data );
			// correggo le coordinate relative alla view, per far si che la texture sia centrata rispetto alla coordinata
			// ( cioè per partire a copiare da in alto a sinistra;
			Vector offset_from_bitmap_point_to_texture_top_left = Vector( point_on_bitmap.GetSize() );
			offset_from_bitmap_point_to_texture_top_left.Set( 0, -(int)(texture->GetColumns()/2.0) );
			offset_from_bitmap_point_to_texture_top_left.Set( 1, -(texture->GetRows()-1) );
			point_on_bitmap.Add( offset_from_bitmap_point_to_texture_top_left );
/*
			// Bitmap *_texture = new Bitmap( 3, 1 );
			for( unsigned int i = 0; i < texture->GetRows(); i++ ){
				for( unsigned int j = 0; j < texture->GetColumns(); j++ ){
					if( i == texture->GetRows()-1 && j == (unsigned int)(texture->GetColumns()/2.0) )
						texture->SetValue( '0', i, j );
					else
						texture->SetValue( '@', i, j );
				}
			}
*/
			data->Copy( texture, point_on_bitmap.GetY(), point_on_bitmap.GetX() );
			this->SetPixel( point_relative_to_bottom_left_view );
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

void DrawLine( ViewPort *view, Level *world, Point2D start, Point2D end ){
	Point2D temp_point = start;
	bool isVertical = false; // la retta è verticale
	double angular_coeffcient = 0.0; // coeff. angolare della retta
	if( end.GetX() - start.GetX() != 0){
		angular_coeffcient = (end.GetY() - start.GetY()) / ( end.GetX() - start.GetX() );
	}
	else{ // il coeff angolare non è definito per tan( 90° )
		isVertical = true;
	}

	view->Draw( NULL, world, start );
	while( ( !isVertical && temp_point.GetX() < end.GetX() ) || ( isVertical && temp_point.GetY() < end.GetY() ) ) {
		if( !isVertical ){
			temp_point.SetX( temp_point.GetX() + 1 );
			temp_point.SetY( (temp_point.GetX()*angular_coeffcient) + temp_point.GetY() ); // y = m*x + q
		}
		else{
			temp_point.SetY( temp_point.GetY() + 1 ); // x = q
		}
		temp_point = world->GetNormalizedPoint( temp_point );
		view->Draw( NULL, world, temp_point );
	}
	view->Draw( NULL, world, end );
}