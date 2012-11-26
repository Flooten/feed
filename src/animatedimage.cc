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
        : image_(image)
    {}

    void AnimatedImage::setAnimation(unsigned int index)
    {
        // Om ett giltigt index
        if (index < image_properties_.nof_animations_)
            image_properties_.current_animation_ = index;
    }

    void AnimatedImage::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        animated = true;
        image_properties_.nof_animations_ = nof_animations;
        image_properties_.nof_frames_ = nof_frames;
        image_properties_.frame_width_ = image_->w / nof_animations;
        image_properties_.frame_height_ = image_->h / nof_frames;
    }

    void AnimatedImage::addTopImage(SDL_Surface* sheet, unsigned int nof_animations, unsigned int nof_frames)
    {
        top_image_ = sheet;
        top_image_properties_.nof_animations_ = nof_animations;
        top_image_properties_.nof_frames_ = nof_frames;
        top_image_properties_.frame_width_ = top_image_->w / nof_animations;
        top_image_properties_.frame_height_ = top_image_->h / nof_frames;
        setTorsoClip();
    }

    void AnimatedImage::setTopFrame(unsigned int index)
    {
        if (index < top_image_properties_.nof_frames_)
            top_image_properties_.current_frame_ = index;
        setTorsoClip();
    }

    void AnimatedImage::setTopRotation(unsigned int index)
    {
        if (index < top_image_properties_.nof_animations_)
            top_image_properties_.current_animation_ = index;
        setTorsoClip();
    }

    void AnimatedImage::update(unsigned int time)
    {
        if (animated)
        {
            unsigned int elapsed_time = time + image_properties_.last_draw_;

            if (elapsed_time >= 1000 / FPS)
            {
                // Dags att byta frame
                advanceFrame();

                // Uppdatera tiden
                image_properties_.last_draw_ = elapsed_time - 1000 / FPS;
            }
            else
            {
                image_properties_.last_draw_ = elapsed_time;
            }
        }
    }

    void AnimatedImage::draw(SDL_Surface* screen, const glm::vec2 position)
    {
        SDL_Rect screen_position_primary = {static_cast<Sint16>(position.x),static_cast<Sint16>(position.y), 0, 0};

        if (animated)
            SDL_BlitSurface(image_, &image_properties_.clip_, screen, &screen_position_primary);
        else
            SDL_BlitSurface(image_, nullptr, screen, &screen_position_primary);

        if (top_image_ != nullptr)
        {
            SDL_Rect screen_position_secondary = {static_cast<Sint16>(position.x),static_cast<Sint16>(position.y), 0, 0};
            SDL_BlitSurface(top_image_, &top_image_properties_.clip_, screen, &screen_position_secondary);
        }
    }

    /*
     *  Private
     */

    void AnimatedImage::advanceFrame()
    {
        if (animated)
        {
            if (image_properties_.current_frame_ == image_properties_.nof_frames_ - 1)
                // Börja om från början
                image_properties_.current_frame_ = 0;
            else
                // Avancera
                ++image_properties_.current_frame_;

            // Uppdatera clip
            image_properties_.clip_ = {static_cast<Sint16>(image_properties_.frame_width_ * image_properties_.current_animation_),
                                       static_cast<Sint16>(image_properties_.frame_height_ * image_properties_.current_frame_),
                                       image_properties_.frame_width_,
                                       image_properties_.frame_height_};
        }
    }

    void AnimatedImage::setTorsoClip()
    {
        top_image_properties_.clip_ = {static_cast<Sint16>(top_image_properties_.frame_width_ * top_image_properties_.current_animation_),
                                       static_cast<Sint16>(top_image_properties_.frame_height_ * top_image_properties_.current_frame_),
                                       top_image_properties_.frame_width_,
                                       top_image_properties_.frame_height_};
    }
}
