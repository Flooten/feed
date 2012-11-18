/*
 * FILNAMN:       audio.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson 9105272612 Y3A
 * DATUM:         2012-11-18
 *
 * BESKRIVNING: Audio är en singleton som ansvarar för all ljud-hantering
 *
 */

#ifndef FEED_AUDIO_H
#define FEED_AUDIO_H

#include <SDL/SDL_mixer.h>
#include <string>
#include <map>

namespace feed
{
    class Audio
    {
    public:
        static Audio& instance();

        bool init();
        void clear();

        bool addSoundFx(const std::string& filename);
        bool addMusic(const std::string& filename);

        void removeSoundFx(const std::string& filename);
        void removeMusic(const std::string& filename);

        void playSoundFx(const std::string& filename);
        void playMusic(const std::string& filename);

        void toggleMusic();

        bool soundFxExist(const std::string& filename);
        bool musicExist(const std::string& filename);

    private:
        Audio() = default;
        Audio(const Audio&) = delete;
        Audio& operator=(const Audio&) = delete;

        std::map<std::string, Mix_Chunk*> sound_fx_;
        std::map<std::string, Mix_Music*> music_;
    };
}

#endif // FEED_AUDIO_H
