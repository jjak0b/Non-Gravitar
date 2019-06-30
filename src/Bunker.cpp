#include "Bunker.hpp"
#include "DamageableEntity.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include "Entity.hpp"
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
Bunker::Bunker( Level *world, Point2D origin, double health) : DamageableEntity( world, origin, NULL, "Bunker", health){}

bool Bunker::Update(GameEngine* game) {
	bool update_result = this->Entity::Update( game );
    int t = game->GetTime()*100;
    this->counter++;
    return update_result;
}

Projectile *Bunker::shoot( Vector direction ){
	Point2D projectile_origin = this->GetOrigin();
	projectile_origin.Add( direction ); 
	Projectile *p = new Projectile( this->world, projectile_origin, direction, 10, "Projectile" );
	return p;
}

int Bunker::random(int range){
    
    int r1 = (rand() % range);
    int r2 = (rand()% range) - range;
    int r3 = (rand() % 2);

    if (r3 == 0) return r1;
    else return r2;
}



