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
    {
        font_ = TTF_OpenFont("data/font.ttf", 14);
    }

    Ui::~Ui()
    {
        TTF_CloseFont(font_);
    }

    void Ui::update()
    {
        health_bar_size_.x = player_->get_health();
        armor_bar_size_.x = player_->get_armor();
        clip_size_ = player_->get_current_weapon()->get_clip();
        ammo_size_ = player_->get_current_weapon()->get_ammo();
        if (font_ != nullptr)
        {
            clip_text_ = TTF_RenderText_Solid(font_, std::to_string(clip_size_).c_str(), text_color_);
            ammo_text_ = TTF_RenderText_Solid(font_, std::to_string(ammo_size_).c_str(), text_color_);
        }
    }

    void Ui::draw(SDL_Surface* screen)
    {
        if (ui_image_ != nullptr)
            util::blitSurface(ui_image_, ui_size_, screen, ui_pos_);

        if (health_bar_image_ != nullptr)
            util::blitSurface(health_bar_image_, health_bar_size_, screen, health_bar_pos_);

        if (armor_bar_image_ != nullptr)
            util::blitSurface(armor_bar_image_, armor_bar_size_, screen, armor_bar_pos_);

        if (clip_text_ != nullptr)
            util::blitSurface(clip_text_, screen, clip_text_pos_.x, clip_text_pos_.y);

        if (ammo_text_ != nullptr)
            util::blitSurface(ammo_text_, screen, ammo_text_pos_.x, ammo_text_pos_.y);
    }
}