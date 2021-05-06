/**
 * @file Music.cpp.cc
 * @brief A simple class wrapper around SDL Mixer component. Specifically for Music.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 03/05/2021
 */


#include "Music.h"
#include "HelperFunctions.h"

Music::Music(const std::string &filePath) : mMusic(Mix_LoadMUS(filePath.c_str()))
{
    if (!mMusic) { throwWarning("Could not load specified sound file."); }
}

Music::~Music()
{
    Mix_FreeMusic(mMusic);
    mMusic = nullptr;
}

void Music::play()
{
    // Todo: Make sure to uncomment this when you want the music back.
    Mix_FadeInMusic(mMusic, -1, 5000);
}


