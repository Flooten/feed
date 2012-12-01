/*
 * FILNAMN:       weapon.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Marcus Eriksson   910322-1371     Y3A
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
        enum Type
        {
            PISTOL,
            SMG,
            SHOTGUN,
            ENEMY_PISTOL,
            UNKNOWN
        };

    	Weapon(int type, int rate_of_fire, int max_clip, int max_ammo, int damage, SDL_Surface* image);

    	SDL_Surface* get_image() const;

    	void addAmmo(int value);
    	void reload();
    	void fired();
        void update(float delta_time);

        bool isReady();

        int get_type() const;
    	int get_clip() const;
    	int get_ammo() const;

        static Weapon* CreateWeapon(int type);

    private:
        int type_ = UNKNOWN;
    	float rate_of_fire_ = 0;
    	float last_fired_ = 0;
    	int clip_ = 0;
    	int max_clip_ = 0;
    	int ammo_ = 0;
    	int max_ammo_ = 0;
    	int damage_ = 0;

        SDL_Surface* image_;
    };
}

 #endif
