#include "Bunker.hpp"
#include "BunkerA.hpp"
#include "DamageableEntity.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>

    
BunkerA::BunkerA( Level *world, Point2D origin) : Bunker( world, origin, 300){
}


bool BunkerA::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );
    
    if (this->counter >= 60) {

        srand(time(0));
        int r1 = random(4);
        int r2 = random (4);
        while (r1 == r2) r2 = random(4);

        Vector *d1 = new Vector();
        d1->Set(0,r1);
        d1->Set(1,1);
        shoot(*d1);

        d1->Set(0,r2);
        d1->Set(1,1);
        shoot(*d1);
 
        counter = 0;
    }
    
    std::list<Entity*> ents = this->world->GetEntities( "Bunker", true, false );
	for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
		if( this->IsColliding( *it, NULL ) ){
				this->Callback_OnCollide( *it, this->GetOrigin() );
				update_result = this->GetHealth() > 0;
		}
	}
    return update_result;

}


void BunkerA::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage( proj->GetDamage());
			proj->Callback_OnCollide( collide_ent, hitOrigin );
		}
		else{ 
			this->DoDamage( this->GetHealth());
		}
	}

}
