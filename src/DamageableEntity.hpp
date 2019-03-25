#pragma once

#include "Entity.hpp"

class DamageableEntity : public Entity{
    protected:
    double MaxHealth;
    double health;

    public:
    DamageableEntity( Level *world, Point2D origin, ColoredBitmap *texture, char *classname, double health );

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
     * @brief infigge una quantità di danno a questa entità, specificando eventualmente colui che lo ha inflitto, l'origine del danno
     * PostCondition: richiama Entity::this.Callback_onHit(...)
     * @param amount 
     * @param attacker 
     * @param damageOrigin 
     */
	void DoDamage( double amount, Point2D damageOrigin, Entity *attacker );

    /**
     * @brief recupera una quantità di vita a questa entità
     * 
     * @param amount 
     * @return double 
     */
    double DoHeal( double amount );

    void Callback_OnHit( Point2D hitOrigin, Entity *attacker, double damage );

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
}