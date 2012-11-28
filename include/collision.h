#ifndef FEED_COLLISION_H
#define FEED_COLLISION_H

#include "object.h"
#include <iostream>

namespace feed
{
    bool isIntersecting(const Object* obj1, const Object* obj2)
    {
        glm::vec2 diff = glm::abs((obj1->get_position() + obj1->get_size() / 2.0f) - 
                                  (obj2->get_position() + obj2->get_size() / 2.0f));

        if (diff.x < ((obj1->get_size().x) / 2 + (obj2->get_size().x) / 2) &&
            diff.y < ((obj1->get_size().y) / 2 + (obj2->get_size().y) / 2))
            return true;

        return 0;
    }

    void handleCollision(Object* obj1, Object* obj2)
    {
        if (isIntersecting(obj1, obj2))
        {
            std::cout << "Is colliding" << std::endl;

            glm::vec2 diff = obj1->get_position() - obj2->get_position();

            glm::vec2 new_pos = obj1->get_position();

            if (diff.y < 0)
                new_pos.y = obj2->get_position().y - obj1->get_size().y;
            else
                new_pos.y = obj2->get_position().y + obj2->get_size().y;

            obj1->set_position(new_pos);
        }
    }
}

#endif
