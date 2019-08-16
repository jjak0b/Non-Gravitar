#include "Bunker.hpp"
#include "Projectile.hpp"
#include "engine/GameEngine.hpp"

Bunker::Bunker( Level *world, Point2D origin, double health, const char classname[]) : DamageableEntity( world, origin, NULL, classname, health ){
	
}

bool Bunker::Update(GameEngine* game) {
	bool update_result = this->Entity::Update( game );
    int t = game->GetTime()*100;
    this->counter++;
    return update_result;
}

Projectile *Bunker::Shoot(Point2D projectile_origin, Vector direction ){
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

