#include "Player.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"

Player::Player( Level *world, Point2D origin, double health ) : DamageableEntity( world, origin, NULL, "Player", health ){
    this->SetOrigin( origin );
    this->world = world;
    /*this->texture = ColoredBitmap( 5, 5, 0 );
    const BITMAP_DATA_TYPE raw_texturer0[] = " ███ ";
    const BITMAP_DATA_TYPE raw_texturer1[] = " ███ ";
    const BITMAP_DATA_TYPE raw_texturer2[] = "@███@";
    const BITMAP_DATA_TYPE raw_texturer3[] = " \\█/ ";
    const BITMAP_DATA_TYPE raw_texturer4[] = "  @  ";
    const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2, raw_texturer3, raw_texturer4 };
    this->texture.Load( rawtexture, 5, 5 );*/
    this->texture = ColoredBitmap( 1, 1, 0 );

}

void Player::Update( GameEngine *game ){
    char input = game->GetkeyPressed();
    Point2D current_origin = this->GetOrigin();
    switch (input)
    {
        case 'w':
            this->SetOrigin( Point2D( current_origin.x, current_origin.y + 1 ) );
            break;
        case 's':
            this->SetOrigin( Point2D( current_origin.x, current_origin.y - 1 ) );
            break;
        case 'a':
            this->SetOrigin( Point2D( current_origin.x - 1 , current_origin.y ) );
            break;
        case 'd':
            this->SetOrigin( Point2D( current_origin.x + 1, current_origin.y + 1 ) );
            break;
        default:
            break;
    }
}