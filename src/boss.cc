/*
 * FILNAMN:       boss.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "boss.h"
#include "messagequeue.h"
#include "resources.cc"

namespace feed
{
    Boss::Boss(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec2& velocity,
               SDL_Surface* image,
               int hitpoints,
               int armor)
        : Character(position,
                    size,
                    velocity,
                    image,
                    hitpoints,
                    armor,
                    hitpoints,
                    armor)    
        {}

    unsigned int Boss::get_inventory_index() const
    {
        return inventory_index_;
    }

    Inventory* Boss::get_inventory()
    {
        return &inventory_;
    }

    Weapon* Boss::get_current_weapon()
    {
        return inventory_.get_item(inventory_index_);
    }

    void Boss::addWeapon(Weapon::Type weapon_type, int ammo)
    {
        inventory_.add(weapon_type, ammo);
    }

    void Boss::set_inventory_index(unsigned int index)
    {
        if (index >= inventory_.get_size())
            return;

        inventory_index_ = index;

        updateTorso();
    }


    void Boss::fire()
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

    void Boss::update (float delta_time)
    {
        Weapon* weapon = inventory_.get_item(inventory_index_);

        if (weapon != nullptr)
            weapon->update(delta_time);

        Character::update(delta_time);
    }


    void Boss::updateTorso()
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
