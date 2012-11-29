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

        glm::vec2 point1 = player->get_position();
        glm::vec2 point2 = env_object->get_position();
        glm::vec2 point3 = enemy->get_position() - point1;
        glm::vec2 point4 = env_object->get_size();


        float det  = ((point4.x * point3.y) - (point3.x * point4.y));
            if (det == 0)
                return true;

        float u1 = (((point1.x - point2.x) * point3.y - (point1.y - point2.y) * (point3.x))/det);
        float u2 = ((-(-(point1.x - point2.x) * point4.y + (point1.y - point2.y) * point4.x))/det);

        return (u1 < 0 || u1 > 1  || u2 < 0  ||  u2 > 1);
    }

    bool onScreen(const Object* obj, const Player* player)
    {
        int obj_x = obj->get_position().x;
        int player_x = player->get_position().x;

        int delta_x =  obj_x - player_x;

        return ((delta_x < util::SCREEN_WIDTH - util::PLAYER_OFFSET_X && delta_x > 0) ||
                (- delta_x - obj->get_size().x < util::PLAYER_OFFSET_X && delta_x < 0));
    }
}
