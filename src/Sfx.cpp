/**
 * @file Sfx.cpp.cc
 * @brief A simple class wrapper around SDL Mixer component.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 03/05/2021
 */


#include "Sfx.h"
#include "HelperFunctions.h"

Sfx::Sfx(const std::string& filePath) : mSound(Mix_LoadWAV(filePath.c_str()))
{
    if (!mSound) { throwError("Could not load specified sound."); }
}

Sfx::~Sfx()
{
    Mix_FreeChunk(mSound);
    mSound = nullptr;
}

void Sfx::play()
{
    Mix_PlayChannelTimed(-1, mSound, 0, -1);
}
