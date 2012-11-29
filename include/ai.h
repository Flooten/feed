/*
 * FILNAMN:       ai.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Mattias Fransson
 * DATUM:         2012-11-28
 *
 * BESKRIVNING: Kollisionshantering
 *
 */

#ifndef FEED_AI_H
#define FEED_AI_H

namespace feed
{
    bool lineOfSight(const class Enemy* enemy, const class Player* player, const class EnvironmentObject* env_object);
    bool onScreen(const class Object* obj, const class Player* player);

}

#endif
