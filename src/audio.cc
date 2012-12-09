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

    bool Audio::addSoundFx(const std::string& key, const std::string& filename)
    {
        if (!soundFxExist(key))
        {
            Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());

            if (chunk == nullptr)
                return false;

            sound_fx_.insert(std::make_pair(key, chunk));
        }

        return true;
    }

    bool Audio::addMusic(const std::string& key, const std::string& filename)
    {
        if (!musicExist(key))
        {
            Mix_Music* music = Mix_LoadMUS(filename.c_str());

            if (music == nullptr)
                return false;

            music_.insert(std::make_pair(key, music));
        }

        return true;
    }

    void Audio::removeSoundFx(const std::string& key)
    {
        auto it = sound_fx_.find(key);
        
        if (it != sound_fx_.end())
        {
            Mix_FreeChunk(it->second);
            sound_fx_.erase(it);
        }
    }

    void Audio::removeMusic(const std::string& key)
    {
        auto it = music_.find(key);
        
        if (it != music_.end())
        {
            Mix_FreeMusic(it->second);
            music_.erase(it);
        }
    }

    void Audio::playSoundFx(const std::string& key)
    {
        auto it = sound_fx_.find(key);

        if (it != sound_fx_.end())
            Mix_PlayChannel(-1, it->second, 0);
    }

    void Audio::playMusic(const std::string& key)
    {
        if (mute_music_)
            return;

        auto it = music_.find(key);

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

    void Audio::pauseMusic()
    {
        if (Mix_PlayingMusic() == 1)
            Mix_PauseMusic();
    }

    void Audio::resumeMusic()
    {
        if (mute_music_)
            return;

        if (Mix_PausedMusic() == 1)
            Mix_ResumeMusic();
    }

    void Audio::stopMusic()
    {
        Mix_HaltMusic();
    }

    void Audio::muteMusic(bool state)
    {
        mute_music_ = state;

        if (mute_music_)
            pauseMusic();
        else
            resumeMusic();
    }

    bool Audio::isMuted() const
    {
        return mute_music_;
    }

    bool Audio::soundFxExist(const std::string& key)
    {
        auto it = sound_fx_.find(key);

        return it != sound_fx_.end();
    }

    bool Audio::musicExist(const std::string& key)
    {
        auto it = music_.find(key);

        return it != music_.end();
    }
}
