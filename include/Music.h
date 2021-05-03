/**
 * @file Music.h
 * @brief A simple class wrapper around SDL Mixer component. Specifically for Music.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 03/05/2021
 */


#ifndef A2OOPGAME_MUSIC_H
#define A2OOPGAME_MUSIC_H


#include <string>
#include <SDL_mixer.h>

/**
 * A simple class wrapper around SDL Mixer component. Specifically for Music.
 * Only one piece of music can be played at any one time.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 03/05/2021]
 */
class Music
{
public:
    explicit Music(const std::string &filePath);
    ~Music();

    void play();
    void pause();
    void reset();
    void mute();

protected:
    Mix_Music *mMusic;
};


#endif //A2OOPGAME_MUSIC_H
