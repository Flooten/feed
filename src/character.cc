/*
 * FILNAMN:       character.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
                  Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-15
 */

#include "character.h"
#include "messagequeue.h"
#include "util.h"

namespace feed
{
    namespace
    {
        const float RAD_TO_DEG = 180 / 3.14159;
        const int DEG_PER_FRAME = 5;
        const int ZERO_DEG_FRAME = 18;
    }

    Character::Character(const glm::vec2& position,
                         const glm::vec2& size,
                         const glm::vec2& velocity,
                         SDL_Surface* image,
                         int hitpoints,
                         int armor,
                         int max_health,
                         int max_armor)
        : Object(position, size, velocity, image)
        , hitpoints_(hitpoints)
        , armor_(armor)
        , max_health_(max_health)
        , max_armor_(max_armor)
    {
        image_->setTopFrame(ZERO_DEG_FRAME);
    }

    void Character::set_aim(glm::vec2 aim)
    {
        aim_ = glm::normalize(aim);

        // Normering
        //aim_ /= aim_.length();

        if (aim.x >= 0)
            image_->setTopFrame(ZERO_DEG_FRAME + ceil((atan(aim_.y / aim_.x) * RAD_TO_DEG)) / DEG_PER_FRAME);
        else
            image_->setTopFrame(ZERO_DEG_FRAME + ceil((atan(aim_.y / -(aim_.x)) * RAD_TO_DEG)) / DEG_PER_FRAME);
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
}
