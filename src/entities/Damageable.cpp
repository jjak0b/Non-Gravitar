#include "Damageable.hpp"

Damageable::Damageable( double healthmax){
	this->SetMaxHealth( healthmax );
	this->SetHealth( healthmax );
	
}

double Damageable::SetMaxHealth( double amount ){
	if (amount < this->health) {
		this->health = amount;
	}

	this->MaxHealth = amount;
	return this->MaxHealth;
}

double Damageable::SetHealth( double amount ){
	this->health = amount;
	return this->health;
}

double Damageable::GetHealth() {
	return this->health;
}

double Damageable::GetMaxHealth() {
	return this->MaxHealth;
}


void Damageable::DoDamage( double amount ) {
	this->health -= amount;
	if (this->health <= 0) {
		this->health = 0;
	}
}

	/**
	 * @brief recupera una quantità di vita a questa entità
	 * 
	 * @param amount 
	 * @return double 
	 */
double Damageable::DoHeal( double amount ) {
	if (this->health += amount > this->MaxHealth) {
		this->health = this->MaxHealth;
	}
	else
	{
		this->health += amount;
	}
	return health;
	
}


 

