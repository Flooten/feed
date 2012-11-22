/*
 * FILNAMN:       character.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-15
 */

#include "character.h"
#include "messagequeue.h"
#include "util.h"
#include <iostream>

namespace feed
{
    Character::Character(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity,
                         SDL_Surface* image, int hitpoints, int armor, int max_health, int max_armor)
                            : Object(position, size, velocity, image)
                            , hitpoints_(hitpoints)
                            , armor_(armor)
                            , max_health_(max_health)
                            , max_armor_(max_armor)
                            {}

    void Character::set_aim(glm::vec2 aim)
    {
        aim_ = aim;
    }

    glm::vec2 Character::get_aim() const
    {
        return aim_;
    }

    void Character::add_health(int value)
    {
        if (hitpoints_ + value > max_health_)
        {
            hitpoints_ = max_health_;
        }
        else if (hitpoints_ + value <= 0)
        {
           MessageQueue::instance().pushMessage({MessageQueue::Message::DEAD, 0, this});
        }
        else
            hitpoints_ += value;
    }

    void Character::add_armor(int value)
    {
        if (armor_ + value > max_armor_)
        {
            armor_ = max_armor_;
        }
        else if (armor_ + value < 0)
        {
            add_health(armor_ + value);
            armor_ = 0;
        }
        else
            armor_ += value;
    }

    void Character::draw(SDL_Surface* screen)
    {
        // Sätt clip
        setClip(counter);
        setColorkey();

        SDL_Rect position = {static_cast<Sint16>(position_.x), static_cast<Sint16>(position_.y), 0, 0};

        // Uppdatera counter
        ++counter;
        if (counter == 7)
        {
            counter = 0;
        }

        if (image_ != nullptr)
        {
            SDL_BlitSurface(image_, &clip_, screen, &position);
        }
    }

    void Character::setClip(int counter)
    {
        clip_ = {static_cast<Sint16>(64 * animation), static_cast<Sint16>(64 * counter), IMAGE_WIDTH, IMAGE_HEIGHT};
    }

    void Character::setColorkey()
    {
        Uint32 colorkey = SDL_MapRGB(image_->format, 255, 0, 255);
        SDL_SetColorKey(image_, SDL_SRCCOLORKEY, colorkey);
    }
}
