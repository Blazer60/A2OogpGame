/**
 * @file Sfx.h
 * @brief A simple class wrapper around SDL Mixer component.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 03/05/2021
 */


#ifndef A2OOPGAME_SFX_H
#define A2OOPGAME_SFX_H

#include <SDL_mixer.h>
#include <string>

/**
 * A simple class wrapper around SDL Mixer component.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 03/05/2021]
 */
class Sfx
{
public:
    explicit Sfx(const std::string& filePath);
    ~Sfx();

    void play();

protected:
    Mix_Chunk *mSound;
};


#endif //A2OOPGAME_SFX_H
