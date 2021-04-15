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
#include "HelperFunctions.h"

#include <iostream>
#include <thread>

StateMachineManager::StateMachineManager(const glm::ivec2 &screenSize, char skipToStateKey) :
    mIsRunning(true), mWindow(nullptr), mScreenSize(screenSize),
    mUpdateRatePerSecond(60.0), mUpdateDelta(1.0 / mUpdateRatePerSecond), mNextUpdateTick(getTicks<double>()),
    mRenderRatePerSecond(90.0), mRenderDelta(1.0 / mRenderRatePerSecond), mNextRenderTick(getTicks<double>())
{
    // Initialise all of SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Could not initialise SDL" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        throw std::exception();
    }

    mWindow = SDL_CreateWindow("A2 OOP Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenSize.x, mScreenSize.y, SDL_WINDOW_SHOWN);
    changeState(skipToStateKey);
}

StateMachineManager::~StateMachineManager()
{
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
    auto stateIterator = mStates.find(stateKey);
    if (stateIterator == mStates.end())
    {
        addState(stateKey);
    }
    mCurrentState = mStates[stateKey];
}

void StateMachineManager::addState(char stateKey)
{
    switch (stateKey)
    {
        case statesList::MainMenu:
        default:
            mStates[stateKey] = std::make_shared<MenuState>(mWindow);
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
    mCurrentState->render(this);
}

void StateMachineManager::runLogic()
{
    while (mIsRunning)
    {
        event();
        update();

        mNextUpdateTick += mUpdateDelta;
        if (getTicks<double>() < mNextUpdateTick)  // Slow the update to sync with real time.
        {
            SDL_Delay(static_cast<Uint32>((mNextUpdateTick - getTicks<double>()) * 1000.0));
        }
    }
}

void StateMachineManager::runRenderer()
{
    while (mIsRunning)
    {
        render();

        mNextRenderTick += mUpdateDelta;
        if (getTicks<double>() < mNextRenderTick)  // Slow the renderer to sync with real time.
        {
            SDL_Delay(static_cast<Uint32>((mNextRenderTick - getTicks<double>()) * 1000.0));
        }
    }
}
