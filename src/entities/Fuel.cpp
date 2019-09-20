#include "Fuel.hpp"
#include "Player.hpp"
#include "Level.hpp"
#include "Projectile.hpp"
#include "engine/Bitmap.hpp"
#include "engine/GameEngine.hpp"
#include "engine/GameConfig.h"
#include "shared/Point2D.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>

Fuel::Fuel( Level *world, Point2D origin) : Entity( world, origin, NULL, "Fuel" ){
}

bool Fuel::Update(GameEngine *game) {
	bool update_result = this->Entity::Update( game );

	// if (update_result) {	
	// 	std::list<Entity*> ents = this->world->GetEntities( "Projectile", false, true );
	// 	for (std::list<Entity*>::iterator it = ents.begin(); update_result && it != ents.end(); it++) {
	// 		if( this->GetShape()->ray_Casting((*it)->GetOrigin()) ){
	// 			Projectile *proj = (Projectile*)(*it);
	// 			if( !strcmp( proj->GetClassname(), "Beam_Projectile" ) ){
	// 			this->GetWorld()->GetPlayer()->DoHeal(this->size);
	// 			update_result = false;
	// 			}
	// 			(*it)->Delete();
	// 		}
	// 	}
	// }

	if (!update_result) this->Delete();
	return update_result;
}

void Fuel::Callback_OnCollide( GameEngine *game, Entity *collide_ent ) {
		if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Player_Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			proj->Delete();
		}
		if( !strcmp( collide_ent->GetClassname(), "Beam_Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			proj->Callback_OnCollide( game, this );
			this->world->GetPlayer()->DoHeal(size);
			this->Delete();
			}

		}

}