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
                    mInputs.left = true;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    mInputs.right = true;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    mInputs.up = true;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    mInputs.down = true;
                    break;
                case SDLK_SPACE:
                    mInputs.space = true;
                    break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_a:
                    mInputs.left = false;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    mInputs.right = false;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    mInputs.up = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    mInputs.down = false;
                    break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            switch (event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    mInputs.leftClick = true;
                    break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            switch (event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    mInputs.leftClick = true;
                    std::cout << "Up";
                    break;
            }
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            mInputs.mousePosition.x = static_cast<float>(event.motion.x);
            mInputs.mousePosition.y = static_cast<float>(event.motion.y);
        }
    }
}

void GameState::update(StateMachineManager *smm)
{
    mPlayer->event(mInputs);
    mPlayer->update();
}

void GameState::render(StateMachineManager *smm, const float &interpolation)
{
    mRenderer.update(interpolation);
    mRenderer.renderItem(mPlayer);
    mRenderer.flip();
}
