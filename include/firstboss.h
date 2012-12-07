/*
 * FILNAMN:       boss.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-12-07
 *
 * BESKRIVNING:
 *
 */

#ifndef FEED_FIRST_BOSS_H
#define FEED_FIRST_BOSS_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "boss.h"
#include <vector>

namespace feed
{
    class FirstBoss : public Boss
    {
    public:
        FirstBoss(const glm::vec2& position,
                  const glm::vec2& size,
                  const glm::vec2& velocity,
                  SDL_Surface* image,
                  int hitpoints,
                  int armor,
                  const glm::vec2& boundary_start  = glm::vec2(0,0),
                  const glm::vec2& boundary_end = glm::vec2(0,0));
  
        void update(float delta_time) override;

    protected:
        void isDead();

    private:
        enum Phase
        {
            PHASE_ONE,
            PHASE_TWO,
            PHASE_THREE
        };

        Phase phase_ = PHASE_ONE;
        int aiming_constant_ = 15;
        float last_updated_aim_ = 0;

        bool spawned_grunts_ = false;
        bool spawned_heavys_ = false;
    };
}

#endif
