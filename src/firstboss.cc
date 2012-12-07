/*
 * FILNAMN:       FirstBoss.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "firstboss.h"
#include "messagequeue.h"

namespace feed
{
    FirstBoss::FirstBoss(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec2& velocity,
               SDL_Surface* image,
               int hitpoints,
               int armor)
        : Boss(position,
                    size,
                    velocity,
                    image,
                    hitpoints,
                    armor)
    {}


    void FirstBoss::update (float delta_time)
    {
        Boss::update(delta_time);
    }
}
