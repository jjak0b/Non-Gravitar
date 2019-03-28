#include "Player.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"

Player::Player( Level *world, Point2D origin, double health ) : DamageableEntity( world, origin, NULL, "Player", health ){
	this->world = world;
    this->SetOrigin( origin );
    /*this->texture = ColoredBitmap( 5, 5, 0 );
    const BITMAP_DATA_TYPE raw_texturer0[] = " ███ ";
    const BITMAP_DATA_TYPE raw_texturer1[] = " ███ ";
    const BITMAP_DATA_TYPE raw_texturer2[] = "@███@";
    const BITMAP_DATA_TYPE raw_texturer3[] = " \\█/ ";
    const BITMAP_DATA_TYPE raw_texturer4[] = "  @  ";
    const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2, raw_texturer3, raw_texturer4 };
    this->texture.Load( rawtexture, 5, 5 );*/
	this->texture = NULL;

}

void Player::Update( GameEngine *game ){
    char input = game->GetkeyPressed();
    Point2D current_origin = this->GetOrigin();	
    switch (input)
    {
        case 'w':
            current_origin.y += 1;
            break;
        case 's':
           current_origin.y -= 1;
            break;
        case 'a':
            current_origin.x -= 1;
            break;
        case 'd':
            current_origin.x += 1;
            break;
        default:
            break;
    }

	if( !current_origin.Equals( this->GetOrigin() ) )
		this->SetOrigin( current_origin );
}