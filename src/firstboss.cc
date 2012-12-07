/*
 * FILNAMN:       FirstBoss.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-12-07
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
               int armor,
               const glm::vec2& boundary_start,
               const glm::vec2& boundary_end)
        : Boss(position,
                    size,
                    velocity,
                    image,
                    hitpoints,
                    armor,
                    boundary_start,
                    boundary_end)
    {}


    void FirstBoss::update(float delta_time)
    {
        Boss::update(delta_time);
    }

    void FirstBoss::isDead()
    {

    }
}
