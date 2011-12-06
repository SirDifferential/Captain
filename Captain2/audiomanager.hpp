#ifndef _AUDIOMANAGER_HPP_
#define _AUDIOMANAGER_HPP_

#include <string>
#ifdef WIN32
#include <SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif

class AudioManager
{
private:
    int id;
    Mix_Music *music;
    Mix_Music *sfx1;
    std::string currentMusicPath;
public:
    AudioManager();
    ~AudioManager();
    
    bool init();
    void startMusic();
    void stopMusic();
    void changeMainMusic(std::string path);
    void playSoundEffect(std::string path);
    void loadAudio(Mix_Music* &audio, std::string path);
    std::string getCurrentMusic() { return currentMusicPath; }
};

#endif
