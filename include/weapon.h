/*
 * FILNAMN:       weapon.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-12-01
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
            BOSS_PISTOL,
            BOSS_SHOTGUN,
            BOSS_SMG,
            UNKNOWN
        };

        Weapon(int type, int rate_of_fire, int max_clip, int max_ammo, SDL_Surface* image);

        SDL_Surface* get_image() const;

        void addAmmo(int value);
        void reload();
        void fired();
        void update(float delta_time);

        bool isReady();

        void set_max_ammo(int max_ammo);
        void set_max_clip(int max_clip);

        int get_type() const;
        int get_clip() const;
        int get_ammo() const;

        static Weapon* createWeapon(int type);

    private:
        int type_ = UNKNOWN;
        float rate_of_fire_ = 0;
        float last_fired_ = 0;
        int clip_ = 0;
        int max_clip_ = 0;
        int ammo_ = 0;
        int max_ammo_ = 0;

        SDL_Surface* image_;
    };
}

 #endif
