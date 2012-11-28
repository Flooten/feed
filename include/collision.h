/*
 * FILNAMN:       collision.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Mattias Fransson
 * DATUM:         2012-11-28
 *
 * BESKRIVNING: Kollisionshantering
 *
 */

#ifndef FEED_COLLISION_H
#define FEED_COLLISION_H

namespace feed
{
    class Object;

    bool isIntersecting(const Object* obj1, const Object* obj2);
    void handleCollision(Object* obj1, Object* obj2);
}

#endif
