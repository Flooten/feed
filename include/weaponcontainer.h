/*
 * FILNAMN:       weaponcontainer.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING: När spelaren interagerar med detta objekt kommer det, om spelaren
 *  			redan har vapnet, att fyllas på med ammunition. Annars läggs det i spelarens inventory
 *
 */

#ifndef FEED_WEAPON_CONTAINER_H
#define FEED_WEAPON_CONTAINER_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "interactableobject.h"

namespace feed
{
    class WeaponContainer : public InteractableObject
    {
    public:
        WeaponContainer(const glm::vec2& position,
                        const glm::vec2& size,
                        int weapon_type,
                        int ammo,
                        SDL_Surface* image);

        virtual void eventFunction() override final;
        int get_ammo() const;

    private:
    	int weapon_type_;
        int ammo_;
    };
}

 #endif
