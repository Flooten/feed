/*
 * FILNAMN:       weaponcontainer.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 */

#include "weaponcontainer.h"
#include "messagequeue.h"

namespace feed
{
    WeaponContainer::WeaponContainer(const glm::vec2& position,
                                     const glm::vec2& size,
                                     SDL_Surface* image,
                                     int weapon_type)
        : InteractableObject(position, size, image)
        , weapon_type_(weapon_type)
    {}

    void WeaponContainer::eventFunction()
    {
    	MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_WEAPON, weapon_type_, this});
    }
}
