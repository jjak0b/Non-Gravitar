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
        this->player = new Player( this, Point2D(0,0), 150 );
    }
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