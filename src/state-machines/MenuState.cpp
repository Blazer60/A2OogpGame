/**
 * @file MenuState.cpp.cc
 * @brief The first state that is loaded when the game is created.
 * Allows the user to play the game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "state-machines/MenuState.h"
#include "state-machines/StateMachineManager.h"

#include "HudText.h"

MenuState::MenuState(SDL_Renderer *renderer, const glm::ivec2 &windowSize) :
    StateMachine(renderer, windowSize, statesList::MainMenu)
{
    mTitle = std::make_shared<HudText>(glm::ivec2(10, 10));
    mTitle->setText("Press P to play the game.");
    mRenderer.loadText(mTitle);
}

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
        if (event.type == SDL_QUIT) { smm->mIsRunning = false; }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    smm->mIsRunning = false;
                    break;
            }
        }
    }

    const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_P]) { smm->changeState(statesList::InGame); }
}

void MenuState::update(StateMachineManager *smm)
{

}

void MenuState::render(StateMachineManager *smm, const float &interpolation)
{
    mRenderer.update(interpolation);

    mRenderer.renderItem(mTitle);
}
