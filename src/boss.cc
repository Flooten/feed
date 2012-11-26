/*
 * FILNAMN:       boss.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-18
 *
 */

#include "boss.h"

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
        (inventory_.get_item(inventory_index_))->fire();
    }
}
