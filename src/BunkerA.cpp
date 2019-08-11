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



BunkerA::BunkerA( Level *world, Point2D origin) : Bunker( world, origin, 300, "BunkerA"){

    this->texture = new ColoredBitmap( 2, 3, 0 );
	const BITMAP_DATA_TYPE raw_texturer0[] = "q_p";
	const BITMAP_DATA_TYPE raw_texturer1[] = "/\xDB\\";
	const BITMAP_DATA_TYPE *rawtexture[] = { raw_texturer0, raw_texturer1};
	this->texture->Load( rawtexture, 2, 3 );

}


bool BunkerA::Update(GameEngine* game) {
    bool update_result = this->Bunker::Update( game );

	if (update_result) {
		if (this->counter >= 40) {
			srand(time(0));
			int r1 = random(4);
			int r2 = random (4);
			while (r1 == r2) r2 = random(4);

			Vector *direction = new Vector();
			direction->Set(0,r1);
			direction->Set(1,1);
			Point2D projectile_origin = Point2D(this->origin.GetX() -1, this->origin.GetY() +1 );
			Shoot( projectile_origin, (*direction));

			direction->Set(0,r2);
			direction->Set(1,1);
			projectile_origin = Point2D(this->origin.GetX() +1, this->origin.GetY() +1 );
			Shoot( projectile_origin, (*direction));

			delete direction;

			counter = 0;
    	}

		BunkerAShape bunker_shape = BunkerAShape(this->GetOrigin());
		std::list<Entity*> ents = this->world->GetEntities( "Projectile", false, true );
		for (std::list<Entity*>::iterator it = ents.begin(); it != ents.end(); it++) {
			if( bunker_shape.PointCollision((*it)->GetOrigin()) ){
				Projectile *proj = (Projectile*)(*it);
				this->DoDamage( proj->GetDamage());
				(*it)->Delete();
				update_result = this->GetHealth() > 0;
			}
		}
    }
	return update_result;
	
}


void BunkerA::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *proj = (Projectile*)collide_ent;
			this->DoDamage( proj->GetDamage());
			proj->Delete();
		}
		else{ 
			this->DoDamage( this->GetHealth());
		}
	}
}


////////////////////////////////////////////////////////////////////
// DEBUG //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void BunkerA::Draw( ViewPort *view ){
	Entity::Draw( view );

	// BunkerAShape test  = BunkerAShape(this->GetOrigin());
	// list<Point2D> points = test.getShapePoints();
	// for (std::list<Point2D>::iterator it = points.begin(); it != points.end(); it++ ) {
	// 	Point2D point= (*it);
	// view->Draw(NULL, this->world, point );
	// }
}
