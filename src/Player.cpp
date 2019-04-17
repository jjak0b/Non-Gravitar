#include "Player.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"
#include "GameConfig.h"
#include "Projectile.hpp"
#include "Point.hpp"
#include <iostream>
#include <list>
#include <iterator>

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

bool Player::Update( GameEngine *game ){
    bool isAlive = true;
    char input = game->GetkeyPressed();
    Point2D current_origin = this->GetOrigin();	
    Vector direction = GetDirectionFromInput( input );
    // eventualmente qui ci potrebbe stare uno Vector.Scale( accel )
    // ed impostare la posizione come spostamento r(t) in base al moto uniformemente accelerato
    current_origin.Add( direction ); // la nuova posizione è uguale alla posizione precedente + il vettore spostamento

	if( !direction.IsNull() ){ // aggiorno la posizione solo il vettore spostamento non è nullo
        this->SetOrigin( current_origin );
        this->lastMove = direction;
    }

    if( this->ShouldFire( input ) ){
        this->Fire( direction );
    }
    else if( this->ShouldBeam( input ) ){
        // TODO: logica del raggio traente
    }
    
    std::list<Entity*> ents = this->world->GetEntities( "Player", true );
    for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it.operator++) {
        Point2D *collisionOrigin = NULL;
        if( this->IsColliding( *it, collisionOrigin ) ){
            this->Callback_OnCollide( *it, *collisionOrigin );
        }
    }
    ents.clear();

    this->lastInput = input;

    return isAlive;
}

Projectile *Player::Fire( Vector direction ){
    Projectile *p = new Projectile( this->world, this->origin, direction, 150 );
    // TODO: Da aggiungere alla lista delle entità
    return p;
}

bool Player::ShouldFire(char input) {
    return input == INPUT_USE_FIRE;
}

bool Player::ShouldBeam(char input) {
    return input == INPUT_USE_BEAM;
}

Vector Player::GetDirectionFromInput( char input ){
    Vector direction = Vector( this->origin.GetSize() );
    switch (input)
    {
        case INPUT_MOVE_UP:
            direction.Set( 1, 1 );
            break;
        case INPUT_MOVE_DOWN:
            direction.Set( 1, -1 );
            break;
        case INPUT_MOVE_LEFT:
            direction.Set( 0, -1 );
            break;
        case INPUT_MOVE_RIGHT:
            direction.Set( 0, 1 );
            break;
        default: // Nessun movimento
            break;
    }

    return direction;
}

char Player::GetLastInput(){
    return this->lastInput;
}
Vector Player::GetLastMove(){
    return this->lastMove;
}

void Player::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
    if( collide_ent != NULL ){
        if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
            Projectile *proj = (Projectile*)collide_ent;
            this->DoDamage( proj->GetDamage(), hitOrigin, proj );
            proj->Callback_OnCollide( collide_ent, hitOrigin );
        }
        else{ // la collisione contro qualsiasi altra entità, danneggia totalmente il giocatore
            this->DoDamage( this->GetHealth(), hitOrigin, collide_ent );
        }
    }
}