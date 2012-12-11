/*
 * FILNAMN:       ai.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 * DATUM:         2012-12-12
 *
 * BESKRIVNING:   Funktioner som används av AI:n.
 *
 */

#ifndef FEED_AI_H
#define FEED_AI_H

namespace feed
{
    bool lineOfSight(const class Enemy* enemy, const class Player* player, const class EnvironmentObject* env_object);
    bool onScreen(const class Object* obj, const class Player* player);
    bool fieldOfVison(const class Enemy* enemy, const class Player* player);
}

#endif
