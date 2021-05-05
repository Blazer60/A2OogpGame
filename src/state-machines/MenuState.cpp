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
    StateMachine(renderer, windowSize, statesList::MainMenu),
    mTextYAdvance(20), mTextYPos(100), mSize(20)
{
    mTitle = std::make_shared<HudText>(glm::ivec2(10, 10));
    mTitle->setText("Press P to play the game.");
    mRenderer.loadText(mTitle);

    addText("Controls:");
    addText("Move   - wasd");
    addText("Dodge  - wasd + space or space");
    addText("Pause  - p");
}

void MenuState::onPause()
{

}

void MenuState::onAwake()
{

}

void MenuState::addText(const std::string& text)
{
    auto textData = std::make_shared<HudText>(glm::ivec2(10, mTextYPos));
    mTextYPos += mTextYAdvance;
    textData->setText(text);
    textData->setSize(mSize);
    mRenderer.loadText(textData);
    mTexts.push_back(textData);
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

    for (auto &item : mTexts)
    {
        mRenderer.renderItem(item);
    }
}
