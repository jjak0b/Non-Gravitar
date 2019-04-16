#include "Player.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"
#include "Projectile.hpp"
#include "Point.hpp"

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

    current_origin.Add( direction );

	if( !current_origin.Equals( this->GetOrigin() ) ){
        this->SetOrigin( current_origin );
        this->lastMove = direction;
    }

    if( this->ShouldFire( input ) ){
        this->Fire( direction );
    }
    else if( this->ShouldBeam( input ) ){
        // TODO: logica del raggio traente
    }

    this->lastInput = input;

    direction.Dispose();
}

Projectile *Player::Fire( Vector direction ){
    Projectile *p = new Projectile( this->world, this->origin, direction, 150 );
    // TODO: Da aggiungere alla lista delle entità
    return p;
}

bool Player::ShouldFire(char input) {
    if (input == 'f')
        return true;
    return false;
}

bool Player::ShouldBeam(char input) {
    if (input == 'r')
        return true;
    return false;
}

Vector Player::GetDirectionFromInput( char input ){
    Vector direction = Vector( this->origin.GetSize() );
    switch (input)
    {
        case 'w':
            direction.Set( 1, 1 );
            break;
        case 's':
            direction.Set( 1, -1 );
            break;
        case 'a':
            direction.Set( 0, -1 );
            break;
        case 'd':
            direction.Set( 0, 1 );
            break;
        default:
            break;
    }
}

char Player::GetLastInput(){

}
Vector Player::GetLastMove(){

}