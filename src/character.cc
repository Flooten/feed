/*
 * FILNAMN:       character.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Marcus Eriksson   910322-1371     Y3A
 *                Mattias Fransson
 * DATUM:         2012-11-29
 */

#include "character.h"
#include "messagequeue.h"
#include "util.h"

#include <iostream>

namespace feed
{
    namespace
    {
        const float RAD_TO_DEG = 180 / 3.14159;
        const int DEG_PER_FRAME = 5;
        const int ZERO_DEG_FRAME = 19;
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
        animation_ = STATIONARY_RIGHT;
        setAnimation(animation_);
    }

    void Character::set_aim(glm::vec2 aim)
    {
        aim_ = glm::normalize(aim);

        if (aim.x >= 0)
            image_->setTopFrame(ZERO_DEG_FRAME + ceil((atan(aim_.y / aim_.x) * RAD_TO_DEG)) / DEG_PER_FRAME);
        else
            image_->setTopFrame(ZERO_DEG_FRAME + ceil((atan(aim_.y / -(aim_.x)) * RAD_TO_DEG)) / DEG_PER_FRAME);
    }

    glm::vec2 Character::get_aim() const
    {
        return aim_;
    }

    int Character::get_health() const
    {
        return hitpoints_;
    }

    int Character::getFacing() const
    {
        return animation_ % 2;
    }

    void Character::addHealth(int value)
    {
        if (hitpoints_ + value > max_health_)
            hitpoints_ = max_health_;
        else if (hitpoints_ + value <= 0)
            isDead();
        else
            hitpoints_ += value;
    }

    void Character::addArmor(int value)
    {
        if (armor_ + value > max_armor_)
        {
            armor_ = max_armor_;
        }
        else if (armor_ + value < 0)
        {
            addHealth(armor_ + value);
            armor_ = 0;
        }
        else
            armor_ += value;
    }

    void Character::update(float delta_time)
    {
        velocity_ += util::GRAVITY * delta_time;

        Object::update(delta_time);
    }

    void Character::setAnimation(Animation animation)
    {
        animation_ = animation;
        image_->setAnimation(animation);
        image_->setTopRotation(animation % 2);
    }

    void Character::jump()
    {
        if (!isJumpLocked())
        {
            if (is_jumping_)
                is_double_jumping_ = true;

            is_jumping_ = true;
            glm::vec2 velocity = get_velocity();
            velocity.y = util::JUMP_VELOCITY;
            set_velocity(velocity);
        }
    }

    void Character::set_jumping(bool state)
    {
        is_jumping_ = state;
        is_double_jumping_ = state;
    }

    bool Character::isJumping() const
    {
        return is_jumping_;
    }

    bool Character::isJumpLocked() const
    {
        return is_jumping_ && is_double_jumping_;
    }
}
