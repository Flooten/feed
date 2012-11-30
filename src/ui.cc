/*
 * FILNAMN:       ui.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-29
 *
 */

#include "ui.h"
#include "util.h"
#include "player.h"
#include <iostream>

namespace feed
{
    Ui::Ui(Player* player, SDL_Surface* image, SDL_Surface* health_bar, SDL_Surface* armor_bar)
        : player_(player)
        , ui_image_(image)
        , health_bar_image_(health_bar)
        , armor_bar_image_(armor_bar)
    {}

    void Ui::update()
    {
        health_bar_size_.x = player_->get_health();
        armor_bar_size_.x = player_->get_armor();
        clip_size_ = player_->get_current_weapon()->get_clip();
        ammo_size_ = player_->get_current_weapon()->get_ammo();
    }

    void Ui::draw(SDL_Surface* screen)
    {
        if (ui_image_ != nullptr)
            util::blitSurface(ui_image_, ui_size_, screen, ui_pos_);

        if (health_bar_image_ != nullptr)
            util::blitSurface(health_bar_image_, health_bar_size_, screen, health_bar_pos_);

        if (armor_bar_image_ != nullptr)
            util::blitSurface(armor_bar_image_, armor_bar_size_, screen, armor_bar_pos_);
    }
}
