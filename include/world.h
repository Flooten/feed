/*
 * FILNAMN:       world.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 * BESKRIVNING: State
 *
 */

#ifndef FEED_WORLD_H
#define FEED_WORLD_H

#include "state.h"

namespace feed
{
    class World : public State
    {
    public:
        virtual void draw(SDL_Surface* screen) override final;
        virtual void update() override final;
        virtual void handleSDLEvent(const SDL_Event& event) override final;
        virtual void handleMessage(const MessageQueue::Message& msg) override final;

    private:
        int i = 0;
    };
}

#endif
