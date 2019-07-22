#include "DamageableEntity.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include <cstring>

DamageableEntity::DamageableEntity( Level *world, Point2D origin, Bitmap *texture, const char classname[], double healthmax) : Entity( world, origin, texture, classname ){
	this->SetMaxHealth( healthmax );
	this->SetHealth( healthmax );
}

double DamageableEntity::SetMaxHealth( double amount ){
	if (amount < this->health) {
		this->health = amount;
	}

	this->MaxHealth = amount;
	return this->MaxHealth;
}

double DamageableEntity::SetHealth( double amount ){
	this->health = amount;
	return this->health;
}

double DamageableEntity::GetHealth() {
	return this->health;
}

double DamageableEntity::GetMaxHealth() {
	return this->MaxHealth;
}


void DamageableEntity::DoDamage( double amount, Point2D damageOrigin, Entity *attacker ) {
	this->health -= amount;
	// if (this-> health -= amount < 0) ???
	//this->Callback_OnHit(damageOrigin, attacker, amount);
}

	/**
	 * @brief recupera una quantità di vita a questa entità
	 * 
	 * @param amount 
	 * @return double 
	 */
double DamageableEntity::DoHeal( double amount ) {
	if (this->health += amount > this->MaxHealth) {
		this->health = this->MaxHealth;
	}
	else
	{
		this->health += amount;
	}
	return health;
	
}

//void Callback_OnHit( Point2D hitOrigin, Entity *attacker, double damage );

void DamageableEntity::Callback_OnCollide( Entity *collide_ent, Point2D hitOrigin ){
	if( collide_ent != NULL ){
		if( !strcmp( collide_ent->GetClassname(), "Projectile" ) ){
			Projectile *e = (Projectile*)collide_ent;
			this->DoDamage( e->GetDamage(), hitOrigin, collide_ent );
		}
	}
}
 