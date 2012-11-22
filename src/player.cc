/*
 * FILNAMN:       player.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "player.h"
#include "messagequeue.h"
#include <iostream>

namespace feed
{
    Player::Player(const glm::vec2& position,
                   const glm::vec2& size,
                   const glm::vec2& velocity,
                   SDL_Surface* image,
                   int hitpoints,
                   int armor,
                   int max_health,
                   int max_armor,
                   unsigned int nof_animations,
                   unsigned int nof_frames)
        : Character(position,
                    size,
                    velocity,
                    image,
                    nof_animations,
                    nof_frames,
                    hitpoints,
                    armor,
                    max_health,
                    max_armor)
    {
        setAnimation(STATIONARY_RIGHT);
    }

    void Player::add_health(int value)
    {
        if (hitpoints_ + value > max_health_)
        {
            hitpoints_ = max_health_;
        }
        else if (hitpoints_ + value <= 0)
        {
           MessageQueue::instance().pushMessage({MessageQueue::Message::PLAYER_DEAD});
        }
        else
            hitpoints_ += value;
    }

    void Player::addWeapon(Weapon& weapon)
    {
        inventory_.add(weapon);
    }

    int Player::get_inventory_index() const
    {
        return inventory_index_;
    }

    void Player::set_inventory_index(int index)
    {
        inventory_index_ = index;
    }

    void Player::fire()
    {
        (inventory_.get_item(inventory_index_))->fire();
    }

    void Player::setAnimation(Animation animation)
    {
        image_->setAnimation(animation);
    }
 }
