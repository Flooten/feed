/*
 * FILNAMN:       enemy.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "enemy.h"

namespace feed
{
    Enemy::Enemy(const glm::vec2& position,
                 const glm::vec2& size,
                 const glm::vec2& velocity,
                 SDL_Surface* image,
                 int hitpoints,
                 int armor,
                 int max_health, 
                 int max_armor,
                 Weapon& weapon,
                 unsigned int nof_animations,
                 unsigned int nof_frames)
        : Character(position,
                    size,
                    velocity,
                    image,
                    nof_animations,
                    nof_frames,
                    hitpoints,
                    armor,
                    max_health,
                    max_armor)
        , weapon_(weapon)
    {}

    void Enemy::fire()
    {
        weapon_.fire();
    }
}
