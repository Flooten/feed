/*
 * FILNAMN:       boss.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 * BESKRIVNING: Denna klass definierar boss. Ärver från Character
 *
 */

#ifndef FEED_BOSS_H
#define FEED_BOSS_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "character.h"
#include "inventory.h"

namespace feed
{
    class Boss : public Character
    {
    public:
        Boss(const glm::vec2& position,
             const glm::vec2& size,
             const glm::vec2& velocity,
             SDL_Surface* image,
             int hitpoints,
             int armor);


        // Getters
        unsigned int get_inventory_index() const;
        Inventory* get_inventory();
        Weapon* get_current_weapon(); 

        // Setters
        void set_inventory_index(unsigned int index);
        void addWeapon(Weapon::Type weapon_type, int ammo = 0);

        void set_inventory_index(int index);
        void fire();

        virtual void update(float delta_time);

    private:
        Inventory inventory_;
        int inventory_index_;

        void updateTorso();

    };
}

#endif
