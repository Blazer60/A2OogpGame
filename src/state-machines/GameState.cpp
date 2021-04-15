/**
 * @file GameState.cpp.cc
 * @brief The game state that runs the actual game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


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
    }
}

void GameState::update(StateMachineManager *smm, const float &deltaTime)
{
    mPlayer->update(deltaTime);
}

void GameState::render(StateMachineManager *smm)
{
    mRenderer.update();
    mRenderer.renderItem(mPlayer);
    mRenderer.flip();
}
