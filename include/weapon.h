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
            ENEMY_PISTOL,
            SHOTGUN,
        };

    	Weapon(int type, int rate_of_fire, int last_fired, int max_clip, int max_ammo, int damage, SDL_Surface* image);

    	SDL_Surface* get_image();

    	void addAmmo(int value);
    	void reload();
    	void fired();
        void update(float delta_time);

        bool isReady();

        int get_type() const;
    	int get_clip() const;
    	int get_ammo() const;

        static Weapon* CreateWeapon(int type, int max_ammo);

    private:
        int type_;
    	float rate_of_fire_;
    	float last_fired_;
    	int clip_ = 0;
    	int max_clip_;
    	int ammo_ = 0;
    	int max_ammo_;
    	int damage_;

        SDL_Surface* image_;
    };
}

 #endif
