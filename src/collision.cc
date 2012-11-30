#include "collision.h"
#include "object.h"
#include "character.h"

#include <iostream>

namespace feed
{
    namespace
    {
        // avstånd i pixlar som man studsar bort från saker
        const int BOUNCE_DISTANCE = 5;
    }

    bool isIntersecting(const Object* obj1, const Object* obj2)
    {
        glm::vec2 offset1 = obj1->get_collision_offset();
        glm::vec2 offset2 = obj2->get_collision_offset();
        glm::vec2 diff = glm::abs((obj1->get_position() + offset1 + obj1->get_size() / 2.0f) - 
                                  (obj2->get_position() + offset2 + obj2->get_size() / 2.0f));

        if (diff.x < (obj1->get_size().x / 2 + obj2->get_size().x / 2) &&
            diff.y < (obj1->get_size().y / 2 + obj2->get_size().y / 2))
            return true;

        return false;
    }

    void handleCollision(Character* obj1, Object* obj2)
    {
        glm::vec2 new_pos = obj1->get_position();
        glm::vec2 new_vel = obj1->get_velocity();

        if (isIntersecting(obj1, obj2))
        {
            glm::vec2 offset1 = obj1->get_collision_offset();
            glm::vec2 offset2 = obj2->get_collision_offset();

            glm::vec2 diff = (obj1->get_position() + offset1 + obj1->get_size() / 2.0f) - 
                             (obj2->get_position() + offset2 + obj2->get_size() / 2.0f);

            if (std::abs(diff.y) >= std::abs(diff.x))
            {
                if (diff.y <= 0.0f)
                {
                    new_pos.y = obj2->get_position().y - offset1.y - obj1->get_size().y;
                    obj1->set_jumping(false);
                }
                else
                {
                    new_pos.y = obj2->get_position().y - offset1.y + obj2->get_size().y;
                }

                new_vel.y = 0.0f;
            }
            else
            {
                if (diff.x <= 0.0f)
                {
                    new_pos.x = obj2->get_position().x - offset1.x - obj1->get_size().x - BOUNCE_DISTANCE;
                    new_vel.x = -BOUNCE_DISTANCE;
                }
                else
                {
                    new_pos.x = obj2->get_position().x - offset1.x + obj2->get_size().x + BOUNCE_DISTANCE;
                    new_vel.x = BOUNCE_DISTANCE;
                }
            }
        }

        obj1->set_position(new_pos);
        obj1->set_velocity(new_vel);
    }

    // bool isIntersecting(const Object* obj1, const Object* obj2)
    // {
    //     glm::vec2 diff = glm::abs((obj1->get_position() + obj1->get_size() / 2.0f) - 
    //                               (obj2->get_position() + obj2->get_size() / 2.0f));

    //     if (diff.x < (obj1->get_size().x / 2 + obj2->get_size().x / 2) &&
    //         diff.y < (obj1->get_size().y / 2 + obj2->get_size().y / 2))
    //         return true;

    //     return false;
    // }

    // void handleCollision(Object* obj1, Object* obj2)
    // {
    //     glm::vec2 current_pos = obj1->get_position();
    //     glm::vec2 new_pos = current_pos;
    //     glm::vec2 current_vel = obj1->get_velocity();
    //     glm::vec2 new_vel = current_vel;

    //     if (isIntersecting(obj1, obj2))
    //     {
    //         glm::vec2 diff = (obj1->get_position() + obj1->get_size() / 2.0f) - 
    //                          (obj2->get_position() + obj2->get_size() / 2.0f);

    //         if (std::abs(diff.y) >= std::abs(diff.x))
    //         {
    //             if (diff.y <= 0.0f)
    //             {
    //                 new_pos.y = obj2->get_position().y - obj1->get_size().y;
    //             }
    //             else
    //             {
    //                 new_pos.y = obj2->get_position().y + obj2->get_size().y;
    //             }

    //             new_vel.y = 0.0f;
    //         }
    //         else
    //         {
    //             if (diff.x <= 0.0f)
    //                 new_pos.x = obj2->get_position().x - obj1->get_size().x;
    //             else
    //                 new_pos.x = obj2->get_position().x + obj2->get_size().x;

    //             //new_vel.x = 0.0f;
    //         }
    //     }

    //     obj1->set_position(new_pos);
    //     obj1->set_velocity(new_vel);
    // }
}
