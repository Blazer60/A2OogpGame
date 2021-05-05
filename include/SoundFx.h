/**
 * @file Sfx.h
 * @brief A simple class wrapper around SDL Mixer component.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 03/05/2021
 */


#ifndef A2OOPGAME_SOUNDFX_H
#define A2OOPGAME_SOUNDFX_H

#include <SDL_mixer.h>
#include <string>

/**
 * A simple class wrapper around SDL Mixer component.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 03/05/2021]
 */
class SoundFx
{
public:
    explicit SoundFx(const std::string& filePath);
    ~SoundFx();

    void play();

protected:
    Mix_Chunk *mSound;
    int mChannel;
};


#endif //A2OOPGAME_SOUNDFX_H
