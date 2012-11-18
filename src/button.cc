/*
 * FILNAMN:       button.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "button.h"
#include "messagequeue.h"

namespace feed
{
    /*
     *  Public
     */
    Button::Button(SDL_Surface* background, const Type type)
        : background_(background)
        , type_(type)

    {
        initClips();
    }

    // Skickar ett specifikt meddelande till MessageQueue.
    void Button::pressed() const
    {
        switch (type_)
        {
        case Button::NEW_GAME:
            MessageQueue::instance().pushMessage({MessageQueue::Message::NEW_GAME});
            break;
        case Button::LOAD_GAME:
            MessageQueue::instance().pushMessage({MessageQueue::Message::LOAD_GAME});
            break;
        case Button::QUIT_GAME:
            MessageQueue::instance().pushMessage({MessageQueue::Message::QUIT_GAME});
            break;
        default:
            break;
        }        
    }

    // Knappen tänds upp.
    void Button::mouseEntered()
    {
        active_ = true;
    }

    // Knappen släcks ned.
    void Button::mouseLeft()
    {
        active_ = false;
    }

    void Button::draw(SDL_Surface* screen, const glm::vec2& position)
    {
        if (background_ != nullptr)
        {
            SDL_Rect screen_position = {static_cast<short>(position.x), static_cast<short>(position.y), 0, 0};

            if (active_)
            {
                // Rita upplyst knapp
                SDL_BlitSurface(background_, &clip_[1], screen, &screen_position);
            }
            else
            {
                // Rita nedsläckt knapp
                SDL_BlitSurface(background_, &clip_[0], screen, &screen_position);
            }
        }
    }

    /*
     *  Private
     */
    void Button::initClips()
    {
        // Nedsläckt
        clip_[0].x = 0;
        clip_[0].y = 0;
        clip_[0].h = HEIGHT;
        clip_[0].w = WIDTH;

        // Upplyst
        clip_[1].x = WIDTH;
        clip_[1].y = 0;
        clip_[1].h = HEIGHT;
        clip_[1].w = WIDTH;
    }
}
