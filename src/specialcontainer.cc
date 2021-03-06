/*
 * FILNAMN:       specialcontainer.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-12-12
 *
 */

#include "specialcontainer.h"
#include "messagequeue.h"
#include "audio.h"

namespace feed
{
    SpecialContainer::SpecialContainer(const glm::vec2& position,
                                   const glm::vec2& size,
                                   SDL_Surface* image,
                                   std::string type)
        : InteractableObject(position, size, image)
        , type_(type)
    {}
    
    void SpecialContainer::eventFunction()
    {
        if(type_ == "spawnboss")
            MessageQueue::instance().pushMessage({MessageQueue::Message::SPAWN_WALL, 0, this});
        if(type_ == "elevatormusic")
            Audio::instance().playMusic("elevator");
        if(type_ == "level01music")
            Audio::instance().playMusic("level01");

    }
}
