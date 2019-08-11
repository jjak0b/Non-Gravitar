#include "SmallFuel.hpp"
#include "SmallFuelShape.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

SmallFuel::SmallFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
    this->size = 50;

	this->texture = new ColoredBitmap( 1, 4, 0 );
	const BITMAP_DATA_TYPE raw_texturer0[] = " [\xFE]";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0 };
	this->texture->Load( rawtexture, 1, 4 );
}

bool SmallFuel::Update(GameEngine *game) {
    bool update_result = this->Fuel::Update(game);

    if ( update_result) {
		SmallFuelShape fuel_shape = SmallFuelShape(this->GetOrigin());
		std::list<Entity*> ents = this->world->GetEntities( "Beam", false, true );
		for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
			if( fuel_shape.PointCollision((*it)->GetOrigin()) ){
                game->GetCurrentLevel()->GetPlayer()->AddFuel(this->size);
				Projectile *proj = (Projectile*)(*it);
				this->Delete();
				(*it)->Delete();
				update_result = false;
			}
		}
    }

    return update_result;
}