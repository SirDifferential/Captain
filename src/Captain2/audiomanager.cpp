#include "audiomanager.hpp"
#include "manager.hpp"

//#define NOMUSIC

AudioManager::AudioManager()
{
    fprintf(stderr, "Audiomanager being hired...\n");
}

AudioManager::~AudioManager()
{
    fprintf(stderr, "Audiomanager being fired...\n");
    Mix_CloseAudio();
}

bool AudioManager::init()
{
    currentMusicPath = "data/music/preacher.it";
#ifndef NOMUSIC
    fprintf(stderr, "Intializing: SDL_mixer\n");
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
    loadAudio(music, currentMusicPath);
    Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
#endif
    return true;
}

void AudioManager::startMusic()
{
    fprintf(stderr, "Playing music\n");
    if(Mix_PlayMusic(music, -1) == -1)
    {
        fprintf(stderr, "Mix_PlayMusic error: %s\n", Mix_GetError());
        manager.getEnter();
        manager.stop();
    }
}

void AudioManager::stopMusic()
{
    fprintf(stderr, "Stopping music\n");
    Mix_HaltMusic();
}

void AudioManager::playSoundEffect(std::string path)
{
    sfx1 = Mix_LoadMUS(path.c_str());
    Mix_PlayMusic(sfx1, 1);
}

void AudioManager::changeMainMusic(std::string path)
{
    fprintf(stderr, "Changing main music to: %s\n", path.c_str());
    currentMusicPath = path;
    stopMusic();
    loadAudio(music, path);
    startMusic();
}

void AudioManager::loadAudio(Mix_Music* &audio, std::string path)
{
    audio = NULL;
    audio = Mix_LoadMUS(path.c_str());
    if (audio == NULL)
    {
        fprintf(stderr, "Error loading music: %s\n", SDL_GetError());
        manager.getEnter();
        manager.stop();
    }
}
