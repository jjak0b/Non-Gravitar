#pragma once

/**
 * @brief Classe indipendente indicante un oggetto danneggiabile
 * 
 */
class Damageable {
	protected:
	double MaxHealth;
	double health;

	public:
	Damageable( double health );

	/**
	 * @brief Restituisce la vita attuale dell'entità
	 * 
	 * @return double 
	 */
	double GetHealth();

	/**
	 * @brief Restituisce la vita massima che può avere l'entità
	 * 
	 * @return double 
	 */
	double GetMaxHealth();

	/**
	 * @brief infigge una quantità di danno a questa entità,
	 * @param amount 
	 */
	void DoDamage( double amount );

	/**
	 * @brief recupera una quantità di vita a questa entità
	 * 
	 * @param amount 
	 * @return double 
	 */
	double DoHeal( double amount );

	protected:
	/**
	 * @brief Imposta la vita massima si questa entità
	 * PostCondition: se la attuale vita è > della vita massima, allora la vita viene normalizzata in base alla vita massima
	 * 
	 * @param amount 
	 * @return double 
	 */
	double SetMaxHealth( double amount );

	/**
	 * @brief Imposta la vita di questa entità
	 * 
	 * @param amount 
	 * @return double 
	 */
	double SetHealth( double amount );

	
};