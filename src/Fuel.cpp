#include "Player.hpp"
#include "Level.hpp"
#include "ColoredBitmap.hpp"
#include "GameEngine.hpp"
#include "GameConfig.h"
#include "Point2D.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <cstring>
#include "Fuel.hpp"

Fuel::Fuel( Level *world, Point2D origin,  double size) : Entity( world, origin, NULL, "Fuel" ){
	
}

bool Fuel::Update(GameEngine *game) {
	bool update_result = this->Entity::Update( game );

    std::list<Entity*> proj = this->world->GetEntities( "Beam", false, true );
	for (std::list<Entity*>::iterator it = proj.begin(); it != proj.end(); it++) {
		if( this->IsColliding( *it, NULL )){
				this->world->GetPlayer()->AddFuel(this->size);
				this->Callback_OnCollide();
				(*it)->Callback_OnCollide();
				
				update_result = false;
		}
	}
    return update_result;
}

