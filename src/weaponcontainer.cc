/*
 * FILNAMN:       weaponcontainer.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-12-12
 *
 */

#include "weaponcontainer.h"
#include "messagequeue.h"

namespace feed
{
    WeaponContainer::WeaponContainer(const glm::vec2& position,
                                     const glm::vec2& size,
                                     int weapon_type,
                                     int ammo,
                                     SDL_Surface* image)
        : InteractableObject(position, size, image)
        , weapon_type_(weapon_type)
        , ammo_(ammo)
    {}

    void WeaponContainer::eventFunction()
    {
    	MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_WEAPON, weapon_type_, this});
    }

    int WeaponContainer::get_ammo() const
    {
        return ammo_;
    }
}
