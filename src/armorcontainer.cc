/*
 * FILNAMN:       armorcontainer.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 */

#include "armorcontainer.h"
#include "messagequeue.h"

namespace feed
{
    ArmorContainer::ArmorContainer(const glm::vec2& position,
                                   const glm::vec2& size,
                                   SDL_Surface* image,
                                   int armor_value,
                                   unsigned int nof_animations,
                                   unsigned int nof_frames)
        : InteractableObject(position, size, image, nof_animations, nof_frames)
        , armor_value_(armor_value)
    {}
    
    void ArmorContainer::eventFunction()
    {
    	MessageQueue::instance().pushMessage({MessageQueue::Message::ADD_ARMOR, armor_value_, this});
    }
}
