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
#include <iostream>

Music::Music(const std::string &filePath) : mMusic(Mix_LoadMUS(filePath.c_str())), mCurrIndex(0)
{
    mFilePaths.push_back(filePath);
    if (!mMusic) { throwWarning("Could not load specified sound file."); }
}

Music::Music(std::vector<std::string> &filePaths) : mMusic(nullptr), mCurrIndex(0)
{
    mFilePaths = std::move(filePaths);
    mCurrIndex = rand() % mFilePaths.size();
    load();
}

Music::~Music()
{
    Mix_FreeMusic(mMusic);
    mMusic = nullptr;
}

void Music::load()
{
    Mix_FreeMusic(mMusic);
    mMusic = Mix_LoadMUS(mFilePaths[mCurrIndex].c_str());
    if (!mMusic) { throwWarning("Could not load sound with index: " + std::to_string(mCurrIndex)); }
    // Rand is good enough for us.
    mCurrIndex = (mCurrIndex + rand()) % static_cast<int>(mFilePaths.size());
}

void Music::update()
{
    if (!Mix_PlayingMusic())
    {
        std::cout << "Switching" << std::endl;
        load();
        play(false);
    }
}

void Music::play(bool loop)
{
    Mix_FadeInMusic(mMusic, loop, 5000);
}


