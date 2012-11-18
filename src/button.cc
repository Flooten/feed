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

    void Button::set_position(const glm::vec2& position)
    {
        position_.x = position.x;
        position_.y = position.y;
    }

    // Skickar ett specifikt meddelande till MessageQueue.
    void Button::pressed() const
    {
        switch (type_)
        {
        case NEW_GAME:
            MessageQueue::instance().pushMessage({MessageQueue::Message::NEW_GAME});
            break;
        case LOAD_GAME:
            MessageQueue::instance().pushMessage({MessageQueue::Message::LOAD_GAME});
            break;
        case QUIT_GAME:
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

    bool Button::isMouseOver(const glm::vec2& mouse_position)
    {
        if ((mouse_position.x > position_.x) &&
            (mouse_position.x < position_.x + WIDTH) &&
            (mouse_position.y > position_.y) &&
            (mouse_position.y < position_.y + HEIGHT))
            // Innanför knappen
            return true;
        else
            // Utanför
            return false;
    }

    void Button::draw(SDL_Surface* screen)
    {
        if (background_ != nullptr)
        {
            if (active_)
            {
                // Rita upplyst knapp
                SDL_BlitSurface(background_, &clip_[1], screen, &position_);
            }
            else
            {
                // Rita nedsläckt knapp
                SDL_BlitSurface(background_, &clip_[0], screen, &position_);
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
