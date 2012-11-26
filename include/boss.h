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
             int armor, 
             int max_health,
             int max_armor,
             Inventory& inventory);

        int get_inventory_index() const;
        void set_inventory_index(int index);
        void fire();

    private:
        Inventory inventory_;
        int inventory_index_;
    };
}

#endif
