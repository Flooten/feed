/*
 * FILNAMN:       ai.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 * DATUM:         2012-11-28
 *
 * BESKRIVNING: 
 *
 */

 #include "util.h"
#include "ai.h"
#include "enemy.h"
#include "player.h"
#include "object.h"
#include "environmentobject.h"
#include <iostream>


namespace feed
{
    bool lineOfSight(const Enemy* enemy, const Player* player, const EnvironmentObject* env_object)
    {
        glm::vec2 offset = glm::vec2(50,30);
        glm::vec2 point1 = player->get_position() + offset;
        glm::vec2 point2 = env_object->get_position();
        glm::vec2 point3 = enemy->get_position() - player->get_position() + offset;
        glm::vec2 point4 = env_object->get_size();

        float det = ((point4.x * point3.y) - (point3.x * point4.y));
            if (det == 0)
                return true;

        float u1 = (((point1.x - point2.x) * point3.y - (point1.y - point2.y) * (point3.x))/det);
        float u2 = ((-(-(point1.x - point2.x) * point4.y + (point1.y - point2.y) * point4.x))/det);

        return (u1 < 0 || u1 > 1  || u2 < 0  ||  u2 > 1);
    }

    bool onScreen(const Object* obj, const Player* player)
    {

        glm::vec2 delta =  obj->get_position() - player->get_position(); 

        return (((delta.x < util::SCREEN_WIDTH - util::PLAYER_OFFSET_X && delta.x > 0) ||
                 (- delta.x - obj->get_size().x < util::PLAYER_OFFSET_X && delta.x < 0))) &&
                ((- delta.y - obj->get_size().y < util::PLAYER_OFFSET_Y && delta.y < 0) || 
                (delta.y < util::SCREEN_HEIGHT - util::PLAYER_OFFSET_Y && delta.y > 0));
    }
}
