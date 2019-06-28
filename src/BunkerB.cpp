#include "Bunker.hpp"
#include "BunkerB.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include <ctime>    
#include <cstdlib>  
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>

    
BunkerB::BunkerB( Level *world, Point2D origin) : Bunker( world, origin, 300){
}


bool BunkerB::Update(GameEngine* game) {
    
    bool update_result = this->Bunker::Update( game );
    if (health <= 0) {
        this->garbage = true;
        
    }
    if (this->counter >= 60) {

        Vector *d1 = new Vector();
        d1->Set(0,-1);
        d1->Set(1,1);
        shoot(*d1);
        
        d1->Set(0,0);
        d1->Set(1,1);
        shoot(*d1);
        
        d1->Set(0,1);
        d1->Set(1,1);
        shoot(*d1);
        
        delete d1;

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

void BunkerB::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
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
