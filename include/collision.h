/*
 * FILNAMN:       collision.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Mattias Fransson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING: Kollisionshantering
 *
 */

#ifndef FEED_COLLISION_H
#define FEED_COLLISION_H

namespace feed
{
    class Object;
    class Character;

    bool isIntersecting(const Object* obj1, const Object* obj2);
    bool isIntersectingX(const Object* obj1, const Object* obj2);
    bool isIntersectingY(const Object* obj1, const Object* obj2);

    void handleCollision(Character* obj1, Object* obj2);
    void handleCollisionY(Character* obj1, Object* obj2);

}

#endif
