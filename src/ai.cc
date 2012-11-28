
#include "ai.h"
#include "enemy.h"
#include "player.h"
#include "environmentobject.h"
#include <iostream>


namespace feed
{
bool line_of_sight(const Enemy* enemy, const Player* player, const EnvironmentObject* env_object)
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

    std::cout << "u1: " << u1 << " u2: " << u2 << " det: " << det << std::endl;

    return (u1 < 0 || u1 > 1  || u2 < 0  ||  u2 > 1);

    //return !((u1 >= 0 && u1 <= 1) && (u2 >= 0 && u2 <= 1));



    // glm::vec2 point1 = enemy->get_position();
    // glm::vec2 point2 = player->get_position();
    // glm::vec2 point3 = env_object->get_position();
    // glm::vec2 point4 = env_object->get_position() + env_object->get_size();

    // float den  = ((point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y));
    // if (den == 0)
    //     return false;

    // float num1 = ((point4.x - point3.x) * (point1.y - point3.y) - (point4.y - point3.y) * (point1.x - point3.x));
    // float num2 = ((point2.x - point1.x) * (point1.y - point3.y) - (point2.y - point1.y) * (point1.x - point3.x));
    // float u1 = num1/den;
    // float u2 = num2/den;

    // //if (den == 0 and num1 == 0 and num2 == 0)
    // //    return false
    // if (u1 < 0 or u1 > 1 or u2 < 0 or u2 > 1)
    //     return true;
    // else
    //     return false;
}
}
