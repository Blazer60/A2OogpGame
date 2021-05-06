/**
 * @file StateMachineManager.cpp.cc
 * @brief Handles all of the states loaded within the game and runs the core game loop.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "StateMachineManager.h"
#include "StateMachine.h"
#include "MenuState.h"
#include "GameState.h"
#include "HelperFunctions.h"
#include "PauseState.h"
#include "DeathState.h"

#include <iostream>
#include <thread>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

StateMachineManager::StateMachineManager(const glm::ivec2 &screenSize, char skipToStateKey) :
    mIsRunning(true), mWindow(nullptr), mScreenSize(screenSize),
    mUpdateRatePerSecond(30.0), mUpdateDelta(1.0 / mUpdateRatePerSecond), mNextUpdateTick(0.0), mUpdateFrameSkip(5),
    mRenderRatePerSecond(90.0), mRenderDelta(1.0 / mRenderRatePerSecond), mNextRenderTick(0.0), mRenderFrameSkip(5),
    mInterpolation(0.0), mMasterVolumePercentage(1.f), mMusicVolumePercentage(1.f), mSoundVolumePercentage(1.f)
{
    // Initialise all of SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { throwError("Could not initialise SDL"); }

    // Initialise SDL Image.
    if (!IMG_Init(IMG_INIT_PNG)) { throwError("Could not load SDL Image with PNG images."); }

    // Initialise SDL Mixer.
    if (!Mix_Init(MIX_INIT_MP3)) { throwError("Could not load SDL Mixer with MP3 enabled."); }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        throwError("Could not load SDL Mixer. Make sure that it is using the correct dlls.");
    }

    // Initialise SDL ttf. TTF is weird and has -1 as the fail flag.
    if (TTF_Init() == -1) { throwError("Could not load SDL ttf. Make sure that all of the dll files exists."); }

    mWindow = SDL_CreateWindow("A2 OOP Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenSize.x, mScreenSize.y, SDL_WINDOW_SHOWN);

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    changeState(skipToStateKey);
}

StateMachineManager::~StateMachineManager()
{
    // Destroy all states before continuing.
    mStates.erase(mStates.begin(), mStates.end());

    // Something in SDL Mixer is handled async. Attempting to free memory
    // causes a crash. Luckily this is called right at the end of the program
    // so it isn't too much of a problem. (Crashes in ~Music())
    //Mix_Quit();
    IMG_Quit();
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

void StateMachineManager::run()
{
    std::thread renderThread(&StateMachineManager::runRenderer, this);
    runLogic();
    renderThread.join();
}

void StateMachineManager::changeState(char stateKey)
{
    if (mCurrentState) { mCurrentState->onPause(); }
    auto stateIterator = mStates.find(stateKey);
    if (stateIterator == mStates.end()) { addState(stateKey); }

    mCurrentState = mStates[stateKey];
    if (stateIterator != mStates.end()) { mCurrentState->onAwake(); }

    // Going to the menu attempts to destroy all other states
    if (stateKey == statesList::MainMenu)
    {
        removeState(statesList::InGame);
        removeState(statesList::Paused);
        removeState(statesList::DeathScreen);
    }

}

void StateMachineManager::addState(char &stateKey)
{
    switch (stateKey)
    {
        case statesList::MainMenu:
        default:
            stateKey = statesList::MainMenu;  // Fail safe in case the state doesn't exist.
            mStates[statesList::MainMenu] = std::make_shared<MenuState>(mRenderer, windowSizeToVec2(mWindow));
            break;
        case statesList::InGame:
            mStates[stateKey] = std::make_shared<GameState>(mRenderer, windowSizeToVec2(mWindow));
            break;
        case statesList::Paused:
            mStates[stateKey] = std::make_shared<PauseState>(
                    mRenderer,
                    windowSizeToVec2(mWindow),
                    std::weak_ptr<StateMachine>(mStates[statesList::InGame]),
                    mMasterVolumePercentage
                    );
            break;
        case statesList::DeathScreen:
            mStates[stateKey] = std::make_shared<DeathState>(
                    mRenderer,
                    windowSizeToVec2(mWindow),
                    std::weak_ptr<StateMachine>(mStates[statesList::InGame])
                    );
            break;
    }
}

void StateMachineManager::removeState(char stateKey)
{
    mStates.erase(stateKey);
}

void StateMachineManager::event()
{
    mCurrentState->event(this);
}

void StateMachineManager::update()
{
    mCurrentState->update(this);
}

void StateMachineManager::render()
{
    mCurrentState->render(this, static_cast<float>(mInterpolation));
    mCurrentState->flip();
}

void StateMachineManager::runSynchronous()
{
    mNextUpdateTick = getTicks<double>();
    unsigned int loopAmount;
    while (mIsRunning)
    {
        loopAmount = 0;
        while (getTicks<double>() > mNextUpdateTick && loopAmount < mUpdateFrameSkip)
        {
            event();
            update();

            mNextUpdateTick += mUpdateDelta;
            loopAmount++;
        }

        mInterpolation = (getTicks<double>() + mUpdateDelta - mNextUpdateTick) / mUpdateDelta;
        render();
    }
}

void StateMachineManager::runLogic()
{
    mNextUpdateTick = getTicks<double>();
    unsigned int loopAmount;
    while (mIsRunning)
    {
        loopAmount = 0;  // If the update is behind, force check to see if the user has quit.
        while (getTicks<double>() > mNextUpdateTick && loopAmount < mUpdateFrameSkip)
        {
            event();
            update();

            mNextUpdateTick += mUpdateDelta;
            loopAmount++;
        }
    }
}

void StateMachineManager::runRenderer()
{
    mNextRenderTick = getTicks<double>();
    unsigned int loopAmount;
    while (mIsRunning)
    {
        loopAmount = 0;  // If the renderer is behind, force check to see if the user has quit.
        while (getTicks<double>() > mNextRenderTick && loopAmount < mRenderFrameSkip)
        {
            mInterpolation = (getTicks<double>() + mUpdateDelta - mNextUpdateTick) / mUpdateDelta;
            render();

            mNextRenderTick += mRenderDelta;
            loopAmount++;
        }
    }
}

void StateMachineManager::setVolume(char channel, float percentage, bool isAdditive)
{
    if (isAdditive)
    {
        switch (channel)
        {
            case soundChannel::Master:
            default:
                mMasterVolumePercentage = glm::clamp(mMasterVolumePercentage + percentage, 0.f, 1.f);
                break;
            case soundChannel::Music:
                mMusicVolumePercentage = glm::clamp(mMusicVolumePercentage + percentage, 0.f, 1.f);
                break;
            case soundChannel::Sound:
                mSoundVolumePercentage = glm::clamp(mSoundVolumePercentage + percentage, 0.f, 1.f);
        }
    }
    else
    {
        switch (channel)
        {
            case soundChannel::Master:
            default:
                mMasterVolumePercentage = percentage;
                break;
            case soundChannel::Music:
                mMusicVolumePercentage = percentage;
                break;
            case soundChannel::Sound:
                mSoundVolumePercentage = percentage;
        }
    }


    // Sets the sound volume.
    Mix_Volume(-1, static_cast<int>(mMasterVolumePercentage * mSoundVolumePercentage * static_cast<float>(MIX_MAX_VOLUME)));

    // Sets the music volume.
    Mix_VolumeMusic(static_cast<int>(mMasterVolumePercentage * mMasterVolumePercentage * static_cast<float>(MIX_MAX_VOLUME)));
}

float StateMachineManager::getVolume(char channel) const
{
    switch (channel)
    {
        case soundChannel::Master:
        default:
            return mMasterVolumePercentage;
        case soundChannel::Music:
            return mMusicVolumePercentage;
        case soundChannel::Sound:
            return mSoundVolumePercentage;
    }
}
