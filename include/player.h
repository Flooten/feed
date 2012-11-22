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
        struct RGB
        {
            unsigned int r;
            unsigned int g;
            unsigned int b;
        };

        Player(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec2& velocity,
               SDL_Surface* image,
               int hitpoints,
               int armor,
               int max_health,
               int max_armor,
               unsigned int nof_animations = 0,
               unsigned int nof_frames = 0);

        enum Animation
        {
            STATIONARY_RIGHT,
            STATIONARY_LEFT,
            WALK_RIGHT,
            WALK_LEFT
        };        

        void setAnimation(Animation animation);
        void addWeapon(Weapon& weapon);
        void add_health(int value);
        int get_inventory_index() const;
        void set_inventory_index(int index);
        void fire() override final;

    private:
        int inventory_index_;
        Inventory inventory_;
    };
}

#endif
