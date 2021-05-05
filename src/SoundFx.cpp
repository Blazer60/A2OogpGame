/**
 * @file Sfx.cpp.cc
 * @brief A simple class wrapper around SDL Mixer component.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 03/05/2021
 */


#include "SoundFx.h"
#include "HelperFunctions.h"

SoundFx::SoundFx(const std::string& filePath) : mSound(Mix_LoadWAV(filePath.c_str())), mChannel(0)
{
    if (!mSound) { throwWarning("Could not load specified sound."); }
}

SoundFx::~SoundFx()
{
    Mix_FreeChunk(mSound);
    mSound = nullptr;
}

void SoundFx::play()
{
    mChannel = Mix_PlayChannelTimed(-1, mSound, 0, -1);
}
