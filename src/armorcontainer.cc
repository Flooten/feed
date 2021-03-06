/*
 * FILNAMN:       armorcontainer.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-12-12
 *
 */

#include "armorcontainer.h"
#include "messagequeue.h"

namespace feed
{
    ArmorContainer::ArmorContainer(const glm::vec2& position,
                                   const glm::vec2& size,
                                   SDL_Surface* image,
                                   int armor_value)
        : InteractableObject(position, size, image)
        , armor_value_(armor_value)
    {}
    
    void ArmorContainer::eventFunction()
    {
    	MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_ARMOR, armor_value_, this});
    }
}
