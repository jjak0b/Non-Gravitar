#include "Player.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"

Player::Player( Level *world, Point2D origin, double health ) : DamageableEntity( world, origin, NULL, "Player", health ){
    this->SetOrigin( origin );
    this->world = world;
    this->texture = ColoredBitmap( 5, 5, 0 );
    // BITMAP_DATA_TYPE *rawTexture = { PLAYER_ROW_BITMAP };
    BITMAP_DATA_TYPE rawTextureR0[] = { ' ', '█', '█', '█', ' '};
    BITMAP_DATA_TYPE rawTextureR1[] = { ' ', '█', '█', '█', ' '};
    BITMAP_DATA_TYPE rawTextureR2[] = { '@', '█', '█', '█', '@'};
    BITMAP_DATA_TYPE rawTextureR3[] = { ' ', '\\','█', '/', ' '};
    BITMAP_DATA_TYPE rawTextureR4[] = { ' ', ' ', '@', ' ', ' '};
    BITMAP_DATA_TYPE* rawtexture[] = { rawTextureR0, rawTextureR1, rawTextureR2, rawTextureR3, rawTextureR4 };
    this->texture.load( rawtexture, 5, 5 );
}