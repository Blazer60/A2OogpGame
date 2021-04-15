/**
 * @file GameState.cpp.cc
 * @brief The game state that runs the actual game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include <iostream>
#include "GameState.h"
#include "StateMachineManager.h"

GameState::GameState(SDL_Window *window) :
    StateMachine(window),
    mPlayer(std::make_shared<Player>(glm::vec2{ 50.f, 50.f }, glm::vec2{ 100.f, 100.f }))
{}

void GameState::onPause()
{

}

void GameState::onAwake()
{

}

void GameState::event(StateMachineManager *smm)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            smm->mIsRunning = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_a:
                    mKeysPressed.left = true;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    mKeysPressed.right = true;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    mKeysPressed.up = true;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    mKeysPressed.down = true;
                    break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_a:
                    mKeysPressed.left = false;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    mKeysPressed.right = false;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    mKeysPressed.up = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    mKeysPressed.down = false;
                    break;
            }
        }
    }
}

void GameState::update(StateMachineManager *smm)
{
    mPlayer->event(mKeysPressed);
    mPlayer->update();
}

void GameState::render(StateMachineManager *smm, const float &interpolation)
{
    mRenderer.update(interpolation);
    mRenderer.renderItem(mPlayer);
    mRenderer.flip();
}
