/*
 * FILNAMN:       player.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-12-01
 *
 */

#include "player.h"
#include "messagequeue.h"
#include "resources.h"
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

    unsigned int Player::get_inventory_index() const
    {
        return inventory_index_;
    }

    Inventory* Player::get_inventory()
    {
        return &inventory_;
    }

    Weapon* Player::get_current_weapon()
    {
        return inventory_.get_item(inventory_index_);
    }

    void Player::addWeapon(Weapon::Type weapon_type, int ammo)
    {
        std::cout << "Lägger till ett vapen med " << ammo << " kulor!" << std::endl;
        inventory_.add(weapon_type, ammo);
    }

    void Player::set_inventory_index(unsigned int index)
    {
        if (index >= inventory_.get_size())
            return;

        inventory_index_ = index;

        updateTorso();
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
                if(!god_mode_)
                    weapon->fired();
            }
        }
    }

    void Player::reload()
    {
        get_current_weapon()->reload();
    }

    void Player::update(float delta_time)
    {
        Weapon* weapon = inventory_.get_item(inventory_index_);

        if (weapon != nullptr)
            weapon->update(delta_time);

        Character::update(delta_time);
    }

    void Player::set_god_mode(bool val)
    {
        god_mode_ = val;
    } 

    bool Player::godMode()
    {
        return god_mode_;
    }

    void Player::addHealth(int value)
    {
        if(!god_mode_)
            Character::addHealth(value);
    }

    void Player::incrementInventory()
    {
        ++inventory_index_;

        if (inventory_index_ >= inventory_.get_size())
            inventory_index_ = 0;

        updateTorso();
    }

    void Player::decrementInventory()
    {
        if (inventory_index_ == 0)
            inventory_index_ = inventory_.get_size();

        --inventory_index_;

        updateTorso();
    }

    ///////////////
    // Protected

    void Player::isDead()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::PLAYER_DEAD, 0, this});
    }

    void Player::updateTorso()
    {
        switch(get_current_weapon()->get_type())
        {
            case Weapon::PISTOL:
                setTopImage(Resources::instance()["player-torso-pistol"], 2, 37);
                break;

            case Weapon::SHOTGUN:
                setTopImage(Resources::instance()["player-torso-shotgun"], 2, 37);
                break;

            case Weapon::SMG:
                setTopImage(Resources::instance()["player-torso-smg"], 2, 37);
                break;
        }
    }
}
