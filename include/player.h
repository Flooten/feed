/*
 * FILNAMN:       player.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
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
        Player(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity,
                  SDL_Surface* image, int hitpoints, int armor, int max_health, int max_armor);

        void addWeapon(Weapon& weapon);
        int get_inventory_index() const;
        void set_inventory_index(int index);
        void fire() override final;

    private:
        int inventory_index_;
        Inventory inventory_;
    };
}

#endif
