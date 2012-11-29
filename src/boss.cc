/*
 * FILNAMN:       boss.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "boss.h"
#include "messagequeue.h"

namespace feed
{
    Boss::Boss(const glm::vec2& position,
               const glm::vec2& size,
               const glm::vec2& velocity,
               SDL_Surface* image,
               int hitpoints,
               int armor,
               int max_health,
               int max_armor,
               Inventory& inventory)
        : Character(position,
                    size,
                    velocity,
                    image,
                    hitpoints,
                    armor,
                    max_health,
                    max_armor)
        , inventory_(inventory)
    {}

    int Boss::get_inventory_index() const
    {
        return inventory_index_;
    }

    void Boss::set_inventory_index(int index)
    {
        inventory_index_ = index;
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
}
