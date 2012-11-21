/*
 * FILNAMN:       button.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-21
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

    void Button::handleMouseMotionEvent(const SDL_MouseMotionEvent& event)
    {
        if (mouseIsOver(event.x, event.y))
            // Lys upp knappen
            mouseEntered();
        else
            // Släck knappen
            mouseLeft();
    }

    void Button::handleMouseButtonEvent(const SDL_MouseButtonEvent& event) const
    {
        if (mouseIsOver(event.x, event.y))
            // Skicka meddelande
            pressed();
    }

    void Button::draw(SDL_Surface* screen)
    {
        if (background_ != nullptr)
        {
            if (active_)
                // Rita upplyst knapp
                SDL_BlitSurface(background_, &clip_[1], screen, &position_);
            else
                // Rita nedsläckt knapp
                SDL_BlitSurface(background_, &clip_[0], screen, &position_);
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

    bool Button::mouseIsOver(int mouse_position_x, int mouse_position_y) const
    {

        if ((mouse_position_x > position_.x) &&
            (mouse_position_x < position_.x + WIDTH) &&
            (mouse_position_y > position_.y) &&
            (mouse_position_y < position_.y + HEIGHT))
            // Innanför knappen
            return true;
        else
            // Utanför knappen
            return false;
    }
}
