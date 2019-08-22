#include "Player.hpp"
#include "Level.hpp"
#include "engine/Bitmap.hpp"
#include "engine/GameEngine.hpp"
#include "engine/GameConfig.h"
#include "Projectile.hpp"
#include "shared/Point2D.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include "PlayerShape.hpp"
#include "BunkerAShape.hpp"
#include "BunkerBShape.hpp"
#include "BunkerCShape.hpp"
#include "SurfaceShape.hpp"

Player::Player( Level *world, Point2D origin, double health ) : DynamicEntity( world, origin, NULL, "Player", PLAYER_MAX_SPEED ), Damageable(PLAYER_HEALTH) {
	this->texture = new Bitmap( 3, 5, COLOR_RED );
	const BITMAP_DATA_TYPE raw_texturer0[] = " /^\\ ";
	const BITMAP_DATA_TYPE raw_texturer1[] = "|___|";
	const BITMAP_DATA_TYPE raw_texturer2[] = "/   \\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1, raw_texturer2 };
	this->texture->Load( rawtexture, NULL, 3, 5 );
	this->moveOverride = NULL;
	this->MaxFuel = PLAYER_MAX_FUEL;
	this->fuel = this->MaxFuel;
}

Player::~Player(){
	this->Delete();
}

void Player::Delete(){
	DynamicEntity::Delete();
	this->SetMoveOverride( NULL );
}

bool Player::Update( GameEngine *game ){
	bool update_result = DynamicEntity::Update( game );

	if( update_result ){
		bool b_collision_detected = false;

		// Jacopo: TODO: Iacopo devi spostare la gestione della collisione nel livello Update di Entity
		// COLLISIONE BUNKER /////////////////////////////////////////////////////////////////////////////////////
		PlayerShape player_shape = PlayerShape(this->GetOrigin());
		std::list<Entity*> bunkers = this->world->GetEntities( "BunkerA", false, true );
		for (std::list<Entity*>::iterator it = bunkers.begin(); !b_collision_detected && it != bunkers.end(); it++) {
			BunkerAShape it_shape = BunkerAShape((*it)->GetOrigin());
			if (player_shape.SideCollision((it_shape)) || it_shape.SideCollision((player_shape)))
				b_collision_detected = true;
		}
		bunkers.clear();
		bunkers = this->world->GetEntities( "BunkerB", false, true );
		for (std::list<Entity*>::iterator it = bunkers.begin(); !b_collision_detected && it != bunkers.end(); it++) {
			BunkerBShape it_shape = BunkerBShape((*it)->GetOrigin());
			if (player_shape.SideCollision((it_shape)) || it_shape.SideCollision((player_shape)))
				b_collision_detected = true;
		}
		bunkers.clear();
		bunkers = this->world->GetEntities( "BunkerC", false, true );
		for (std::list<Entity*>::iterator it = bunkers.begin(); !b_collision_detected && it != bunkers.end(); it++) {
			BunkerCShape it_shape = BunkerCShape((*it)->GetOrigin());
			if (player_shape.SideCollision((it_shape)) || it_shape.SideCollision((player_shape)))
				b_collision_detected = true;
		}
		bunkers.clear();

		// COLLISIONE PROJECTILE /////////////////////////////////////////////////////////////////////////////////////
		PlayerShape bunker_shape = PlayerShape(this->GetOrigin());
		std::list<Entity*> projectiles = this->world->GetEntities( "Projectile", false, false );
		for (std::list<Entity*>::iterator it = projectiles.begin(); !b_collision_detected && update_result && it != projectiles.end(); it++) {
			if( bunker_shape.PointCollision((*it)->GetOrigin()) ){
				Projectile *proj = (Projectile*)(*it);
				this->DoDamage( proj->GetDamage());
				(*it)->Delete();
				update_result = this->GetHealth() > 0;
			}
		}
		projectiles.clear();

		// COLLISIONE SURFACE /////////////////////////////////////////////////////////////////////////////////////
		// Jacopo: TODO: Iacopo devi rifare questa perchè non funziona
	/*
		std::list<Point2D> surface = this->world->getSurface();
		std::list<Point2D>::iterator surface_it = surface.begin();
		Point2D start, end;
		while( update_result && !b_collision_detected && surface_it != surface.end() ){
			start = *surface_it;
			surface_it++;
			end = *surface_it;
			SurfaceShape surface_shape = SurfaceShape(start, end);
			if (surface_shape.SideCollision(player_shape))	{
				b_collision_detected = true;
			}
		}
	*/

		// COLLISIONE FINE
		if( IsDefined( this ) ){
			if( !update_result || b_collision_detected || this->GetFuel() <= 0 || this->GetHealth() <= 0 ){
				this->Delete();
			}
		}

		update_result = IsDefined( this );
		if( update_result ) {
			INPUT_TYPE input = game->GetkeyPressed();
			Vector direction;

			if (this->moveOverride != NULL) {
				direction = *this->moveOverride;
			}
			else{
				direction = GetDirectionFromInput(input);
			}
			// this->AddAcceleration( direction.Scale( 5 ) );

			if ( !direction.IsNull() ) { // aggiorno la posizione solo il vettore spostamento non è nullo
				Vector direction_inverted = direction;
				direction_inverted.Scale( -1.0 );
				Vector _velocity = direction;
				if( this->lastMove.Equals( direction_inverted ) ){ // Se il giocatore vuole andare nella direzione opposta, allora lo fermo
					_velocity.Reset();
				}
				else{ // altrimenti va nelal direzione di movimento
					_velocity.Scale( PLAYER_MAX_SPEED );
				}

				this->SetVelocity( _velocity );
				this->lastMove = direction;
			}

			Vector deceleration = this->lastMove;
			if( GetSpeed() > 0.0 ){
#ifndef DEBUG
				this->RemoveFuel( 1 );
#endif
				// deceleration.Scale( 0 );
				// this->AddAcceleration( deceleration );
			}

			if (this->ShouldFire(input)) {
				this->Fire(this->lastMove);
			}
			else if (this->ShouldBeam(input)) {
				this->Beam(this->lastMove);
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


//////////// DEBUG /////////////////////////////////////////////////////////////////////////////
	// PlayerShape test  = PlayerShape(this->GetOrigin());
	// list<Point2D> points = test.getShapePoints();
	// for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
	// 	Point2D point= (*it);
	// view->Draw(NULL, this->world, point );
	// }
////////////////////////////////////////////////////////////////////////////////////////////////



	Point2D point_top_left_hud = Point2D( 0, view->GetHeight() - 2 );
	snprintf( str_print_buffer, size_str_buffer, "Score: [value]"); // TODO: aggiungere valore dopo implementazione
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
	projectile_origin.Add( direction ); // non lo genero nelle stesse coordinate del giocatore
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 10, "Player_Projectile", this->GetMaxSpeed() + 5 );
	return p;
}

Projectile *Player::Beam( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	projectile_origin.Add( direction );
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 0, "Beam_Projectile" );
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

void Player::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage( proj->GetDamage());
			proj->Delete();
		}
		if( !strcmp( collide_ent->GetClassname(), "Beam" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			proj->Delete();
		}
		if( !strcmp( collide_ent->GetClassname(), "Bunker" ) ){
			this->Delete();
		}
	}
}

void Player::SetWorld( Level *_world){
	this->Entity::SetWorld( world );
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