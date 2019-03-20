#include "Player.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"

#define PLAYER_ROW_BITMAP { {0, 0, 0, 0, 0 },\
                            {0, 0, 0, 0, 0 },\
                            {0, 0, 0, 0, 0 },\
                            {0, 0, 0, 0, 0 },\
                            {0, 0, 0, 0, 0 } }
Player::Player( Level *world, Point2D origin ){
    this->SetOrigin( origin );
    this->world = world;
    this->texture = ColoredBitmap( 5, 5, 0 );
    this->texture.load( PLAYER_ROW_BITMAP, 5, 5 );
}