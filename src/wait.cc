#include "wait.h"
#include "util.h"
#include "messagequeue.h"

namespace feed
{
    Wait::Wait(SDL_Surface* background, float secs)
        : background_(SDL_ConvertSurface(background, background->format, SDL_SWSURFACE))
        , wait_(secs)
    {}

    Wait::~Wait()
    {
        SDL_FreeSurface(background_);
    }

    void Wait::draw(SDL_Surface* screen)
    {
        if (background_ != nullptr && screen != nullptr)
            util::blitSurface(background_, screen, 0, 0);
    }

    void Wait::update(float delta_time)
    {
        start_ += delta_time;

        if (start_ >= wait_)
            MessageQueue::instance().pushMessage({MessageQueue::Message::WAIT_DONE});
    }
}
