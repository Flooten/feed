/*
 * FILNAMN:       spikes.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-11-30
 *
 * BESKRIVNING: Spikar som skadar spelaren om han rör vid dem
 *
 */

#ifndef FEED_SPIKES_H
#define FEED_SPIKES_H

#include "interactableobject.h"

namespace feed
{
    class Spikes : public InteractableObject
    {
    public:
        Spikes(const glm::vec2& position,
               const glm::vec2& size,
               SDL_Surface* image,
               int damage);

        void eventFunction() override final;

    private:    
        int damage_;
    };
}

#endif
