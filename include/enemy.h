/*
 * FILNAMN:       enemy.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-26
 *
 * BESKRIVNING: Denna klass definierar en fiende. Ärver från Character
 *
 */

#ifndef FEED_ENEMY_H
#define FEED_ENEMY_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "character.h"
#include "weapon.h"

namespace feed
{
    class Enemy : public Character
    {
    public:
        Enemy(const glm::vec2& position,
              const glm::vec2& size,
              const glm::vec2& velocity,
              SDL_Surface* image,
              int hitpoints,
              int armor,
              int max_health,
              int max_armor,
              int weapon_type);

        ~Enemy();

        void fire();

        bool get_seen_player() const;
        void set_seen_player(bool value);

        void update(float delta_time) override;

        static Enemy* CreateGrunt(const glm::vec2& position);
        static Enemy* CreateHeavy(const glm::vec2& position);

    protected:
        void isDead();

    private:
        Weapon* weapon_;
        bool seen_player_ = true;
    };
}

#endif
