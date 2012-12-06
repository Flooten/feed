#include "collision.h"
#include "object.h"
#include "character.h"

#include <iostream>

namespace feed
{
    namespace
    {
        // Avstånd i pixlar som man studsar bort från saker vid kollision
        const int BOUNCE_DISTANCE = 1000;
        const float FALL_DAMAGE = 0.01f;
    }

    // Returnerar sant om två objekt korsar varandra
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

    // mini-optimering för att slippa räkna ut diff två gånger i handleCollision
    bool isIntersecting(const Object* obj1, const Object* obj2, const glm::vec2& diff)
    {
        return (diff.x < (obj1->get_size().x / 2 + obj2->get_size().x / 2) &&
                diff.y < (obj1->get_size().y / 2 + obj2->get_size().y / 2));
    }

    // Hanterar kollision mellan Character-typer och godtyckliga objekt.
    // obj1 förflyttas vid kollisionen
    void handleCollision(Character* obj1, Object* obj2)
    {
        // används för att beräkna objektets "egentliga" position
        glm::vec2 offset1 = obj1->get_collision_offset();
        glm::vec2 offset2 = obj2->get_collision_offset();

        glm::vec2 diff = (obj1->get_position() + offset1 + obj1->get_size() / 2.0f) - 
                         (obj2->get_position() + offset2 + obj2->get_size() / 2.0f);

        if (isIntersecting(obj1, obj2, glm::abs(diff)))
        {
            // temporärer för uppdatering av position/hastighet
            glm::vec2 new_pos = obj1->get_position();
            glm::vec2 new_vel = obj1->get_velocity();

            // prioritera kollision i y-led över kollision i x-led
            if (std::abs(diff.y) >= std::abs(diff.x))
            {
                if (diff.y <= 0.0f)
                {
                    new_pos.y = obj2->get_position().y - offset1.y - obj1->get_size().y;
                    obj1->set_jumping(false);

                    // fallskada
                    // int damage = obj1->get_velocity().y * FALL_DAMAGE;
                    // obj1->addHealth(-damage);
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
                    new_pos.x = obj2->get_position().x - offset1.x - obj1->get_size().x;// - BOUNCE_DISTANCE;
                    //new_vel.x = BOUNCE_DISTANCE;
                }
                else
                {
                    new_pos.x = obj2->get_position().x - offset1.x + obj2->get_size().x;// + BOUNCE_DISTANCE;
                    //new_vel.x = BOUNCE_DISTANCE;
                }
            }

            obj1->set_position(new_pos);
            obj1->set_velocity(new_vel);
        }
    }
}
