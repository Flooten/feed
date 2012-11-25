/*
 * FILNAMN:       animation.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-23
 *
 */

#include "animatedimage.h"
#include <iostream>

namespace feed
{
    /*
     *  Public
     */

    AnimatedImage::AnimatedImage(SDL_Surface* image)
        : image_sheet_primary_(image)
    {}

    void AnimatedImage::setAnimation(unsigned int index)
    {
        // Om ett giltigt index
        if (index < primary_.nof_animations_)
            primary_.current_animation_ = index;
    }

    void AnimatedImage::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        animated = true;
        primary_.nof_animations_ = nof_animations;
        primary_.nof_frames_ = nof_frames;
        primary_.frame_width_ = image_sheet_primary_->w / nof_animations;
        primary_.frame_height_ = image_sheet_primary_->h / nof_frames;
    }

    void AnimatedImage::addTorsoSheet(SDL_Surface* sheet, unsigned int nof_animations, unsigned int nof_frames)
    {
        image_sheet_secondary_ = sheet;
        secondary_.nof_animations_ = nof_animations;
        secondary_.nof_frames_ = nof_frames;
        secondary_.frame_width_ = image_sheet_secondary_->w / nof_animations;
        secondary_.frame_height_ = image_sheet_secondary_->h / nof_frames;
        setTorsoClip();
    }

    void AnimatedImage::setTorsoFrame(unsigned int index)
    {
        if (index < secondary_.nof_frames_)
            secondary_.current_frame_ = index;
        setTorsoClip();
    }

    void AnimatedImage::setTorsoRotation(unsigned int index)
    {
        if (index < secondary_.nof_animations_)
            secondary_.current_animation_ = index;
        setTorsoClip();
    }

    void AnimatedImage::advanceTorsoFrame()
    {
        // Ändra ej om vi är på sista
        if (secondary_.current_frame_ != secondary_.nof_frames_ - 1)
        {
            ++secondary_.current_frame_;
            setTorsoClip();
        }
    }

    void AnimatedImage::retreatTorsoFrame() 
    {
        // Ändra ej om vi är på första
        if (secondary_.current_frame_ != 0)
        {
            --secondary_.current_frame_;
            setTorsoClip();
        }
    }

    void AnimatedImage::update(unsigned int time)
    {
        if (animated)
        {
            unsigned int elapsed_time = time + primary_.last_draw_;

            if (elapsed_time >= 1000 / FPS)
            {
                // Dags att byta frame
                advanceFrame();

                // Uppdatera tiden
                primary_.last_draw_ = elapsed_time - 1000 / FPS;
            }
            else
            {
                primary_.last_draw_ = elapsed_time;
            }
        }
    }

    void AnimatedImage::draw(SDL_Surface* screen, const glm::vec2 position)
    {
        SDL_Rect screen_position_primary = {static_cast<Sint16>(position.x),static_cast<Sint16>(position.y), 0, 0};

        if (animated)
            SDL_BlitSurface(image_sheet_primary_, &primary_.clip_, screen, &screen_position_primary);
        else
            SDL_BlitSurface(image_sheet_primary_, nullptr, screen, &screen_position_primary);

        if (image_sheet_secondary_ != nullptr)
        {
            // Vi har en tvådelad bild där den övre delen finns i image_sheet_secondary_
            SDL_Rect screen_position_secondary = {screen_position_primary.x, screen_position_primary.y, 0, 0};

            SDL_BlitSurface(image_sheet_secondary_, &secondary_.clip_, screen, &screen_position_secondary);
        }
    }

    /*
     *  Private
     */

    void AnimatedImage::advanceFrame()
    {
        if (animated)
        {
            if (primary_.current_frame_ == primary_.nof_frames_ - 1)
                // Börja om från början
                primary_.current_frame_ = 0;
            else
                // Avancera
                ++primary_.current_frame_;

            // Uppdatera clip
            primary_.clip_ = {static_cast<Sint16>(primary_.frame_width_ * primary_.current_animation_),
                              static_cast<Sint16>(primary_.frame_height_ * primary_.current_frame_),
                              primary_.frame_width_,
                              primary_.frame_height_};
        }
    }

    void AnimatedImage::setTorsoClip()
    {
        secondary_.clip_ = {static_cast<Sint16>(secondary_.frame_width_ * secondary_.current_animation_),
                                static_cast<Sint16>(secondary_.frame_height_ * secondary_.current_frame_),
                                secondary_.frame_width_,
                                secondary_.frame_height_};
    }
}
