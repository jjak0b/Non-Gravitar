#include "BigFuel.hpp"
#include "BigFuelShape.hpp"
#include "Projectile.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

BigFuel::BigFuel( Level *world, Point2D origin) : Fuel( world, origin) {
    
	this->size = 100;

	this->texture = new ColoredBitmap( 2, 4, 0 );
	const BITMAP_DATA_TYPE raw_texturer0[] = " \xC9\xDC\xBB";
	const BITMAP_DATA_TYPE raw_texturer1[] = " \xC8\xDF\xBC";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, 2, 4 );
}

bool BigFuel::Update(GameEngine *game) {
    bool update_result = this->Fuel::Update(game);

    if ( update_result) {
		BigFuelShape fuel_shape = BigFuelShape(this->GetOrigin());
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