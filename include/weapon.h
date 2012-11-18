/*
 * FILNAMN:       weapon.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: 
 *
 */

#ifndef FEED_WEAPON_H
#define FEED_WEAPON_H

#include <SDL/SDL.h>

namespace feed
{
    class Weapon
    {
    public:
    	Weapon(int rate_of_fire, int last_fired, int max_clip, int max_ammo, int damage, SDL_Surface* image);

    	SDL_Surface* get_image();

    	void add_ammo(int value);
    	void reload();
    	void fire();

    	int get_clip();
    	int get_ammo();
    private:
    	int rate_of_fire_;
    	int last_fired_;
    	int clip_ = 0;
    	int max_clip_;
    	int ammo_ = 0;
    	int max_ammo_;
    	int damage_;

        SDL_Surface* image_;
    };
}

 #endif
