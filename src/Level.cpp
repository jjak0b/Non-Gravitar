#include "Entity.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "GameEngine.hpp"

Level::Level(unsigned int MaxWidth, unsigned int MaxHeight, Player *_player ) : Entity( NULL, Point2D(0,0), NULL, "Level" ){
	this->width = MaxWidth;
    this->height = MaxHeight;

    if( _player != NULL ){
        this->player = player;
    }
    else{
		
        this->player = new Player( this, Point2D(  0, 0 ), 150 );
    }
}

void Level::SetOrigin(){
	// Niente
}

Point2D Level::GetNormalizedPoint( Point2D _origin ){
	if( _origin.x < 0 ){
		_origin.x = this->GetMaxWidth() + _origin.x;
	}
	else{
		_origin.x = _origin.x % this->GetMaxWidth();
	}

	if( _origin.y < 0 ){
		_origin.y = 0;
	}
	else if( _origin.y > this->GetMaxHeight() ){ // non >= perchè se y = this->GetMaxHeight() lo consideriamo come fuori dal livello
		_origin.y =  this->GetMaxHeight();
	}

	return _origin;
}

void Level::Update( GameEngine *game ){
    this->player->Update( game ); // temp
    // TODO
}

void Level::Draw( ViewPort *view ){
    this->player->Draw( view ); // temp
    // TODO
}

unsigned int Level::GetMaxHeight(){
    return this->height;
}

unsigned int Level::GetMaxWidth(){
    return this->width;
}

Player *Level::GetPlayer(){
    return this->player;
}