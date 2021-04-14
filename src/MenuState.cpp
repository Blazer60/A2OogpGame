/**
 * @file MenuState.cpp.cc
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "MenuState.h"
#include "StateMachineManager.h"

MenuState::MenuState(SDL_Window *window) : StateMachine(window)
{}

void MenuState::onPause()
{

}

void MenuState::onAwake()
{

}

void MenuState::event(StateMachineManager *smm)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            smm->mIsRunning = false;
        }
    }
}

void MenuState::update(StateMachineManager *smm)
{

}

void MenuState::render(StateMachineManager *smm)
{

}
