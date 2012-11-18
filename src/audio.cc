/*
 * FILNAMN:       audio.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson 9105272612 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "audio.h"

#include <iostream>
#include <utility>

namespace feed
{
    Audio& Audio::instance()
    {
        static Audio instance_;
        return instance_;
    }

    bool Audio::init()
    {
        return !(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1);
    }

    void Audio::clear()
    {
        for (auto& sfx : sound_fx_)
            Mix_FreeChunk(sfx.second);

        for (auto& music : music_)
            Mix_FreeMusic(music.second);

        Mix_CloseAudio();
    }

    bool Audio::addSoundFx(const std::string& filename)
    {
        if (!soundFxExist(filename))
        {
            Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());

            if (chunk == nullptr)
                return false;

            sound_fx_.insert(std::make_pair(filename, chunk));
        }

        return true;
    }

    bool Audio::addMusic(const std::string& filename)
    {
        if (!musicExist(filename))
        {
            Mix_Music* music = Mix_LoadMUS(filename.c_str());

            if (music == nullptr)
                return false;

            music_.insert(std::make_pair(filename, music));
        }

        return true;
    }

    void Audio::removeSoundFx(const std::string& filename)
    {
        auto it = sound_fx_.find(filename);
        
        if (it != sound_fx_.end())
        {
            Mix_FreeChunk(it->second);
            sound_fx_.erase(it);
        }
    }

    void Audio::removeMusic(const std::string& filename)
    {
        auto it = music_.find(filename);
        
        if (it != music_.end())
        {
            Mix_FreeMusic(it->second);
            music_.erase(it);
        }
    }

    void Audio::playSoundFx(const std::string& filename)
    {
        auto it = sound_fx_.find(filename);

        if (it != sound_fx_.end())
            Mix_PlayChannel(-1, it->second, 0);
    }

    void Audio::playMusic(const std::string& filename)
    {
        auto it = music_.find(filename);

        if (it != music_.end())
            Mix_PlayMusic(it->second, -1);
    }

    void Audio::toggleMusic()
    {
        if (Mix_PausedMusic() == 1)
            Mix_ResumeMusic();
        else
            Mix_PauseMusic();
    }

    bool Audio::soundFxExist(const std::string& filename)
    {
        auto it = sound_fx_.find(filename);

        return it != sound_fx_.end();
    }

    bool Audio::musicExist(const std::string& filename)
    {
        auto it = music_.find(filename);

        return it != music_.end();
    }
}
