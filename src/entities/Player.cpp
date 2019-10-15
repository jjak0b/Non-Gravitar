#include "Player.hpp"
#include "Level.hpp"
#include "engine/Bitmap.hpp"
#include "engine/GameEngine.hpp"
#include "engine/GameConfig.h"
#include "Projectile.hpp"
#include "Beam.hpp"
#include "PlanetEntity.hpp"
#include "PlanetLevel.hpp"
#include "shared/Point2D.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include "shared/Utility.h"
#ifdef __WIN32__ // TODO: Rimuovere dopo test
#include <windows.h>
#endif

Player::Player( Level *world, Point2D origin, double health = PLAYER_HEALTH ) : DynamicEntity( world, origin, NULL, "Player", PLAYER_MAX_SPEED ), Damageable(health) {
	this->texture = new Bitmap( 3, 5, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = " /^\\ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = "|___|";
	const BITMAP_DATA_TYPE raw_texturer2[] = "/   \\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2 };
	this->texture->Load( rawtexture, NULL, 3, 5 );
	this->moveOverride = NULL;
	this->MaxFuel = PLAYER_MAX_FUEL;
	this->fuel = this->MaxFuel;
	this->score = 0;

	this->shape = new Shape();
	this->shape->addOffset(Point2D( -2, 6 ), origin);
	this->shape->addOffset(Point2D( -2, 0 ), origin);
	this->shape->addOffset(Point2D( +2, 0 ), origin);
	this->shape->addOffset(Point2D( +2, 6 ), origin);

	
}

Player::~Player(){
	if( moveOverride != NULL ){
	    delete moveOverride;
	}
}

void Player::Delete(GameEngine* game ){;
	this->SetMoveOverride( NULL );
    Entity::Delete( game );
}

bool Player::Update( GameEngine *game ){
	bool update_result = DynamicEntity::Update( game );
	
	if( update_result ){

		// std::list<Entity*> ents = this->world->GetEntities( "Projectile", false, false );
		// for (std::list<Entity*>::iterator it = ents.begin(); update_result && it != ents.end(); it++) {

		// 	if( this->IsColliding(*it) ){
		// 		(*it)->Callback_OnCollide(game, this);
		// 		}
		// 	}
		

		if( IsDefined( this ) ){
			if( !update_result || this->GetFuel() <= 0 || this->GetHealth() <= 0 ){
                update_result = false;
			}
		}

		if ( !update_result ){
            this->Delete( game );
		}
		else{
			INPUT_TYPE input = game->GetkeyPressed();
			Vector direction;

			if (this->moveOverride != NULL) {
				direction = *this->moveOverride;
			}
			else{
				direction = GetDirectionFromInput(input);
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////
			Point2D current_origin = this->GetOrigin();
			current_origin.Add(direction);

			if (!direction.IsNull()) { // aggiorno la posizione solo il vettore spostamento non è nullo
				// this->RemoveFuel(1);
				this->SetOrigin(current_origin);
				this->lastMove = direction;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////

// 			Vector _acceleration = direction;
// 			if ( !direction.IsNull() ) { // aggiorno la posizione solo il vettore spostamento non è nullo
// 				Vector direction_inverted = direction;
// 				direction_inverted.Scale( -1.0 );

// 				if( this->lastMove.Equals( direction_inverted ) ){ // Se il giocatore vuole andare nella direzione opposta, allora lo rallento
// 					_acceleration.Scale( -this->GetSpeed() );
// 				}
// 				else{ // altrimenti va nella direzione di movimento
// 					_acceleration.Scale( PLAYER_MAX_SPEED );
// 				}

// 				_acceleration = direction;
// 				_acceleration.Scale( PLAYER_MAX_ACCELERATION );
// 				this->AddAcceleration( _acceleration );
// 				this->lastMove = direction;
// 			}
// 			// ricevo un rallentamento di "attrito" nella direzione opposta a quella di movimento per rallentare il giocatore, migliorando il suo controllo
// 			_acceleration.Add( GetVelocity().Scale( -PLAYER_FRICTION_COEFFICIENT ) ); // a_f = - v * C

// 			this->AddAcceleration( _acceleration );

// 			if( GetSpeed() > 0.1 ){
// #ifndef DEBUG
// 				this->RemoveFuel( 1 );
// #endif
// 			}

			if (this->ShouldFire(input)) {
				Vector direction = this->GetVelocity();
				direction.Normalize();
				//this->Fire( direction );
				this->Fire(lastMove);
			}
			else if (this->ShouldBeam(input)) {
				Vector direction = this->GetVelocity();
				direction.Normalize();
				//this->Fire( direction );
				this->Fire_Beam();
			}

			this->lastInput = input;
		}
	}
	return update_result;
}

void Player::Draw( ViewPort *view ){
	Entity::Draw( view );

	const int size_str_buffer = 30;
	char str_print_buffer[ size_str_buffer ] = "";

	// HUD del giocatore che mostra il suo status
	Point2D point_top_left_hud = Point2D( 0, view->GetHeight() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Score: %d", this->GetScore());
	view->Print( str_print_buffer, point_top_left_hud, COLOR_RED );

	point_top_left_hud.SetY( point_top_left_hud.GetY() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Fuel: %.2f / %.2f", this->GetFuel(), this->GetMaxFuel() );
	view->Print( str_print_buffer, point_top_left_hud, COLOR_BLUE );

	point_top_left_hud.SetY( point_top_left_hud.GetY() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Health: %.2f / %.2f", this->GetHealth(), this->GetMaxHealth() );
	view->Print( str_print_buffer, point_top_left_hud, COLOR_GREEN );
}

Projectile *Player::Fire( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	
	// TODO: dopo tests sostituire temp con dirextion senza Scale
	Vector temp = direction;
	temp.Scale(6); // Scalo la direzione per farlo sparare oltre la collision shape
	projectile_origin.Add( temp ); // non lo genero nelle stesse coordinate del giocatore

	Projectile *p = new Projectile( this->world, projectile_origin, direction, 50, "Player_Projectile", this->GetMaxSpeed() + 5 );
	return p;
}

Beam *Player::Fire_Beam( ){
	Point2D projectile_origin = this->GetOrigin();
	Vector direction;
	direction.Set(1, -1);
	projectile_origin.Add( direction );
	Vector temp = direction;

	// TODO: dopo tests sostituire temp con dirextion senza Scale
	temp.Scale(6); // Scalo la direzione per farlo sparare oltre la collision shape
	projectile_origin.Add( temp ); // non lo genero nelle stesse coordinate del giocatore

	Beam *p = new Beam( this->world, projectile_origin, direction );
	return p;
}

bool Player::ShouldFire( INPUT_TYPE input ) {
	return input == INPUT_USE_FIRE;
}

bool Player::ShouldBeam( INPUT_TYPE input) {
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

void Player::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Player_Projectile" ) ){
			return;
		}
// #ifdef DEBUG_COLLISION_DRAWING
		cout << " DETECTED COLLISION: " << collide_ent->GetClassname() << endl << "( " << collide_ent->GetOrigin().GetX() << " , " << collide_ent->GetOrigin().GetY() << " ) "<<endl;
		DrawLine(game->view, this->world, this->origin, collide_ent->GetOrigin(), COLOR_RED );
		// Sleep(1000);

// #endif
		// Collisione contro il terreno
		if( Utility::CheckEqualsOrSubstring( collide_ent->GetClassname(), "Level", true ) ){
			// TODO: temp
			// this->DoDamage( this->GetHealth() );
		}
		// Collisione contro un proiettile
		else if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			
#ifdef DEBUG_COLLISION_DRAWING
			DrawLine( game->view, this->world, proj->GetFireOrigin(), collide_ent->GetOrigin(), COLOR_RED );
#else
			this->DoDamage( proj->GetDamage());
#endif
		}
		// Collisione contro un Bunker
		else if( Utility::CheckEqualsOrSubstring( collide_ent->GetClassname(), "Bunker", true ) ){
			// this->DoDamage( this->GetHealth() );
			Sleep(1000);
		}
		else if( !strcmp( collide_ent->GetClassname(), "PlanetEntity" ) ) {
			PlanetEntity* planet = (PlanetEntity*)collide_ent;

			// il punto di fuga è vicino al punto di collisione ma distaccato dal punto di -2(direction) unità,
			// così che nel frame successivo alla fuga dal pianeta non sarà ancora eventualemente considerato come in collisione con esso ( anche se non può accadere )

			// inverto la direzione con la quale si è diretto verso il pianeta
			planet->escape_direction = this->GetVelocity();
			planet->escape_direction.Normalize();
			planet->escape_direction.Scale( -1.0 );

			planet->escape_point = this->GetOrigin();
			Vector escape_offset = planet->escape_direction;
			escape_offset.Scale( 2.0 ); // Aggiungo un offset per esere sicuro di non tornare nuovamente nel raggio di collisioni del pianeta
			planet->escape_point.Add( escape_offset );
			planet->escape_point = planet->GetWorld()->GetNormalizedPoint( planet->escape_point );
			// Il giocatore entra nel Livello

			if( IsDefined( planet->GetPlanetLevel() ) ){
				planet->GetPlanetLevel()->AddEntity( this );
				// Creo il punto di atterraggio nel pianeta
				// GetMaxHeight() è il valore dell'altezza secondo cui si è considerati fuori dal pianeta,
				// quindi dovrà partire dal un'unità più in basso
				Point2D spawn_point = Point2D( 0, this->GetWorld()->GetMaxHeight() - 1 );
				this->SetOrigin( spawn_point );

				Vector direction = Vector( spawn_point.GetSize() );
				direction.Set( 1, -1 );
				VECTOR_VALUE_TYPE speed = this->GetSpeed();
				this->SetVelocity( Vector( direction.GetSize() ) ); // Azzero la velocità attuale, così la velocità iniziale sarà 0
				this->SetVelocity( direction.Scale( speed ) );

				game->SetCurrentLevel( planet->GetPlanetLevel() );
			}
		}
	}
}
		

void Player::SetWorld( Level *_world){
	this->Entity::SetWorld( _world );
}

void Player::SetMoveOverride( Vector *direction ){
	if( this->moveOverride != NULL ){
		delete this->moveOverride;
	}
	this->moveOverride = direction;
}


void Player::SetMaxFuel( double amount ){
	if (amount < this->fuel) {
		this->fuel = amount;
	}

	this->MaxFuel = amount;
}

void Player::SetFuel( double amount ){
	this->fuel = amount;
}

double Player::GetFuel() {
	return this->fuel;
}

double Player::GetMaxFuel() {
	return this->MaxFuel;
}


void Player::AddFuel( double amount ) {
	if (this->fuel + amount > this->MaxHealth) {
		this->fuel = this->MaxFuel;
	}
	else
	{
		this->fuel += amount;
	}

}

void Player::RemoveFuel( double amount ) {
	this->fuel -= amount;
	if (this->fuel < 0) {
		this->fuel = 0;
	}
}

unsigned int Player::GetScore(){
	return this->score;
}

void Player::AddScore(unsigned int value) {
	this->score += value;
}

