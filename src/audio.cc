#include "audio.h"

#include <iostream>

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
        Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());

        if (chunk == nullptr)
            return false;

        // Fixme: kontrollera kollision!
        sound_fx_.insert(std::pair<std::string, Mix_Chunk*>(filename, chunk));

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

    void Audio::playSoundFx(const std::string& filename)
    {
        auto it = sound_fx_.find(filename);

        if (it != sound_fx_.end())
            Mix_PlayChannel(-1, it->second, 0);
    }
}
