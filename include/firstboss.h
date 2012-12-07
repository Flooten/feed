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
                  int armor);
  
        void update(float delta_time) override;

    protected:
        void isDead();

    private:
        Inventory inventory_;
        int inventory_index_;
    };
}

#endif
