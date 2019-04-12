#include "Entity.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "GameEngine.hpp"

#include <iostream>
#include <list>
#include <iterator>
using namespace std;

#include "Projectile.hpp"
#include "Fuel.hpp"

Level::Level(unsigned int MaxWidth, unsigned int MaxHeight, Player *_player) : Entity( NULL, Point2D(0,0), NULL, "Level" ){
	this->width = MaxWidth;
    this->height = MaxHeight;

    if( _player != NULL ){
        this->player = player;
    }
    else{
        this->player = new Player( this, Point2D(  30, 30 ), 150 );
    }	

	list<Projectile*> projectileList;
	this->projectiles = projectileList;
	this->lastInput = 'd';

	/*list<Fuel*> fuelList;
	this->fuel = fuelList;
	Fuel* a = new Fuel(this, Point2D( 5 , 5 ), 25);
	this->fuel.push_back(a);*/
	
	
	
	
};
	

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

	this->checkLastInput( game );
    this->player->Update( game );

	addProjectile(this->player->shoot( game ));


	for (std::list<Projectile*>::iterator it=this->projectiles.begin(); it != this->projectiles.end(); ++it) {
		(*it)->Update();
	}
	removeProjectile();
    
};
	

void Level::Draw( ViewPort *view ){
    this->player->Draw( view );

	/*for (std::list<Fuel*>::iterator it=this->fuel.begin(); it != this->fuel.end(); ++it) {
		(*it)->Draw( view );
	}*/
	for (std::list<Projectile*>::iterator it=this->projectiles.begin(); it != this->projectiles.end(); ++it) {
		(*it)->Draw( view );
	}
	
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

void Level::addProjectile(bool shoot) {
	if (shoot) {
		Projectile* a = new Projectile(this, this->player->GetOrigin(), (this->GetMaxWidth(), this->GetMaxHeight()), 1, this->lastInput);
		this->projectiles.push_back(a);
	}
}

void Level::removeProjectile() {
	for (std::list<Projectile*>::iterator it=this->projectiles.begin(); it != this->projectiles.end(); ++it) {
		Projectile* tmp = *it;
		if(((*it)->GetOrigin().x == 0)
			|| ((*it)->GetOrigin().y == 1)
			|| ((*it)->GetOrigin().x == (this->GetMaxWidth() - 2))
			|| ((*it)->GetOrigin().y == this->GetMaxHeight()) ){
			
			it = this->projectiles.erase(it);
                delete tmp;
			}
	}
}

void Level::checkLastInput( GameEngine* game) {
	
	if (game->GetkeyPressed() == 'w'
		|| game->GetkeyPressed() == 'a'
		|| game->GetkeyPressed() == 's'
		|| game->GetkeyPressed() == 'd') 
		this->lastInput = game->GetkeyPressed();
}

//void Level::addFuel(int n25, int n50) {
	
//	for (int i = 0; i < n25; i++ ) {
		

//}