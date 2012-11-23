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
        : image_sheet_(image)
    {}

    void AnimatedImage::setAnimation(unsigned int index)
    {
        // Om ett giltigt index
        if (index < nof_animations_)
            current_animation_ = index;
    }

    void AnimatedImage::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        animated = true;
        nof_animations_ = nof_animations;
        nof_frames_ = nof_frames;
        frame_width_ = image_sheet_->w / nof_animations_;
        frame_height_ = image_sheet_->h / nof_frames_;
    }

    void AnimatedImage::update(unsigned int time)
    {
        if (animated)
        {
            unsigned int elapsed_time = time + last_draw_;

            if (elapsed_time >= 1000 / FPS)
            {
                // Dags att byta frame
                advanceFrame();

                // Uppdatera tiden
                last_draw_ = elapsed_time - 1000 / FPS;
            }
            else
            {
                last_draw_ = elapsed_time;
            }
        }
    }

    void AnimatedImage::draw(SDL_Surface* screen, const glm::vec2 position)
    {
        SDL_Rect screen_position = {static_cast<Sint16>(position.x),static_cast<Sint16>(position.y), 0, 0};

        if (animated)
            SDL_BlitSurface(image_sheet_, &clip_, screen, &screen_position);
        else
            SDL_BlitSurface(image_sheet_, nullptr, screen, &screen_position);
    }

    /*
     *  Private
     */

    void AnimatedImage::advanceFrame()
    {
        if (animated)
        {
            if (current_frame_ == nof_frames_ - 1)
                // Börja om från början
                current_frame_ = 0;
            else
                // Avancera
                ++current_frame_;

            // Uppdatera clip
            clip_ = {static_cast<Sint16>(frame_width_ * current_animation_),
                     static_cast<Sint16>(frame_height_ * current_frame_),
                     frame_width_,
                     frame_height_};
        }
    }
}
