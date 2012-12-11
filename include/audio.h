/*
 * FILNAMN:       audio.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-12-12
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

        bool addSoundFx(const std::string& key, const std::string& filename);
        bool addMusic(const std::string& key, const std::string& filename);

        void removeSoundFx(const std::string& key);
        void removeMusic(const std::string& key);

        void playSoundFx(const std::string& key);
        void playMusic(const std::string& key);

        void toggleMusic();
        void pauseMusic();
        void resumeMusic();
        void stopMusic();
        void muteMusic(bool state);
        bool isMuted() const;

        bool soundFxExist(const std::string& key);
        bool musicExist(const std::string& key);

    private:
        Audio() = default;
        Audio(const Audio&) = delete;
        Audio& operator=(const Audio&) = delete;

        std::map<std::string, Mix_Chunk*> sound_fx_;
        std::map<std::string, Mix_Music*> music_;

        bool mute_music_ = false;
    };
}

#endif // FEED_AUDIO_H
