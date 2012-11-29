/*
 * FILNAMN:       player.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-29
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
                   int max_armor)
        : Character(position,
                    size,
                    velocity,
                    image,
                    hitpoints,
                    armor,
                    max_health,
                    max_armor)
    {}

    int Player::get_inventory_index() const
    {
        return inventory_index_;
    }

    // void Player::addHealth(int value)
    // {
    //     if (hitpoints_ + value > max_health_)
    //     {
    //         hitpoints_ = max_health_;
    //     }
    //     else if (hitpoints_ + value <= 0)
    //     {
    //        MessageQueue::instance().pushMessage({MessageQueue::Message::PLAYER_DEAD});
    //     }
    //     else
    //         hitpoints_ += value;
    // }

    void Player::addWeapon(Weapon::Type weapon_type)
    {
        std::cout << "Lägger till ett vapen!" << std::endl;
        inventory_.add(weapon_type);
    }    

    void Player::set_inventory_index(int index)
    {
        inventory_index_ = index;
    }

    void Player::fire()
    {
        // Skicka meddelande till messagequeue
        Weapon* weapon = inventory_.get_item(inventory_index_);

        if (weapon != nullptr)
        {
            if (weapon->isReady())
            {
                MessageQueue::instance().pushMessage({MessageQueue::Message::FIRE, weapon->get_type(), this});
                weapon->fired();
            }
        }
    }

    void Player::update(float delta_time)
    {
        Weapon* weapon = inventory_.get_item(inventory_index_);

        if (weapon != nullptr)
            weapon->update(delta_time);

        Character::update(delta_time);
    }

    ///////////////
    // Protected

    void Player::isDead()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::PLAYER_DEAD, 0, this});
    }
}
