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

#include <iostream>
#include <thread>

StateMachineManager::StateMachineManager(const glm::ivec2 &screenSize, char skipToStateKey) :
    mIsRunning(true), mWindow(nullptr), mScreenSize(screenSize)
{
    // Initialise all of SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Could not initialise SDL" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        throw std::exception();
    }

    mWindow = SDL_CreateWindow("A2 OOP Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenSize.x, mScreenSize.y, SDL_WINDOW_SHOWN);
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
//        event();
//        update();
    }
}

void StateMachineManager::runRenderer()
{
    while (mIsRunning)
    {
//        render();
    }
}
