#ifndef FEED_WAIT_H
#define FEED_WAIT_H

#include "state.h"

#include <SDL/SDL.h>

namespace feed
{
    class Wait : public State
    {
    public:
        Wait(SDL_Surface* background, float secs);
        ~Wait();

        void draw(SDL_Surface* screen) override final;
        void update(float delta_time);
        void handleSDLEvent(const SDL_Event&) {}
        void handleMessage(const MessageQueue::Message&) {} 

    private:
        SDL_Surface* background_ = nullptr;
        float wait_ = 0;
        float start_ = 0;
    };

}

#endif
