/*
 * FILNAMN:       player.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-12-01
 *
 * BESKRIVNING: Denna klass definierar spelaren. Ärver från Character
 *
 */

#ifndef FEED_PLAYER_H
#define FEED_PLAYER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "character.h"
#include "inventory.h"

namespace feed
{
    class Player : public Character
    {
    public:
        Player(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec2& velocity,
               SDL_Surface* image,
               int hitpoints,
               int armor,
               int max_health,
               int max_armor);

        // Getters
        unsigned int get_inventory_index() const;
        Inventory* get_inventory();
        Weapon* get_current_weapon(); 

        // Setters
        void set_inventory_index(unsigned int index);
        void addWeapon(Weapon::Type weapon_type, int ammo = 0);
        void fire() override final;
        void reload();
        void update(float delta_time) override;

    private:
        void isDead() override final;

        unsigned int inventory_index_ = 0;
        Inventory inventory_;
    };
}

#endif
