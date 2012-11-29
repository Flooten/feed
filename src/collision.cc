#include "collision.h"
#include "object.h"

#include <iostream>

namespace feed
{
    bool isIntersecting(const Object* obj1, const Object* obj2)
    {
        // glm::vec2 diff = glm::abs((obj1->get_position() + obj1->get_size() / 2.0f) - 
        //                           (obj2->get_position() + obj2->get_size() / 2.0f));

        glm::vec2 pos1(obj1->get_bounding_box().x, obj1->get_bounding_box().y);
        glm::vec2 size1(obj1->get_bounding_box().z, obj1->get_bounding_box().w);
        glm::vec2 pos2(obj2->get_bounding_box().x, obj2->get_bounding_box().y);
        glm::vec2 size2(obj2->get_bounding_box().z, obj2->get_bounding_box().w);

        glm::vec2 diff = glm::abs((pos1 + size1 / 2.0f) -
                                  (pos2 + size2 / 2.0f));

        // if (diff.x < ((obj1->get_size().x) / 2 + (obj2->get_size().x) / 2) &&
        //     diff.y < ((obj1->get_size().y) / 2 + (obj2->get_size().y) / 2))
        //     return true;

        if (diff.x < (size1.x / 2.0f + size2.x / 2.0f) &&
            diff.y < (size1.y / 2.0f + size2.y / 2.0f))
            return true;

        return false;
    }

    void handleCollision(Object* obj1, Object* obj2)
    {
        glm::vec2 current_pos = obj1->get_position();
        glm::vec2 new_pos = current_pos;
        glm::vec2 current_vel = obj1->get_velocity();
        glm::vec2 new_vel = current_vel;

        if (isIntersecting(obj1, obj2))
        {
            glm::vec2 diff = (obj1->get_position() + obj1->get_size() / 2.0f) - 
                             (obj2->get_position() + obj2->get_size() / 2.0f);

            //glm::vec2 diff = obj1->get_position() - obj2->get_position();

            float top1 = obj1->get_position().y;
            float bottom1 = obj1->get_position().y + obj2->get_size().y;
            float left1 = obj1->get_position().x;
            float right1 = obj1->get_position().x + obj2->get_size().x;

            float top2 = obj2->get_position().y;
            float bottom2 = obj2->get_position().y + obj2->get_size().y;
            float left2 = obj2->get_position().x;
            float right2 = obj2->get_position().x + obj2->get_size().x;

            std::cout << "Player pos:\t" << left1 << ", " << top1 << std::endl;
            std::cout << "Player bound:\t" << right1 << ", " << bottom1 << std::endl;
            std::cout << "Box pos:\t" << left2 << ", " << top2 << std::endl;
            std::cout << "Box bound:\t" << right2 << ", " << bottom2 << std::endl;

            if (std::abs(diff.y) >= std::abs(diff.x))
            {
                if (diff.y <= 0.0f)
                {
                    new_pos.y = obj2->get_position().y - obj1->get_size().y;
                }
                else
                {
                    new_pos.y = obj2->get_position().y + obj2->get_size().y;
                }

                new_vel.y = 0.0f;
            }
            else
            {
                if (diff.x <= 0.0f)
                    new_pos.x = obj2->get_position().x - obj1->get_size().x;
                else
                    new_pos.x = obj2->get_position().x + obj2->get_size().x;

                //new_vel.x = 0.0f;
            }
        }

        obj1->set_position(new_pos);
        obj1->set_velocity(new_vel);
    }
}
