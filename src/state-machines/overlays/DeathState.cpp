/**
 * @file DeathState.cpp.cc
 * @brief The death screen that comes up after the
 * player has died within the game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 05/05/2021
 */


#include "DeathState.h"
#include "StateMachineManager.h"
#include "HudText.h"
#include "HudElement.h"

#include <utility>


DeathState::DeathState(SDL_Renderer *renderer, const glm::ivec2 &widowSize, std::weak_ptr<StateMachine> attachedTo) :
        OverlayState(renderer, widowSize, std::move(attachedTo), statesList::DeathScreen)
{
    mTitle = std::make_shared<HudText>(glm::ivec2(-252, 0), HudElement::Middle | HudElement::Center);
    mTitle->setText("MECHA CHAD KILLED YOU");
    mTitle->setSize(40);
    mRenderer.loadText(mTitle);


    mScoreCard = std::make_shared<HudText>(glm::ivec2(-50, -150), HudElement::Bottom | HudElement::Middle);
    mScoreCard->setText("Score");
    mRenderer.loadText(mScoreCard);

    mTip = std::make_shared<HudText>(glm::ivec2(-210, 50), HudElement::Middle | HudElement::Center);
    mTip->setText("Press [esc] to go to the Main Menu.");
    mTip->setSize(20);
    mRenderer.loadText(mTip);
}

void DeathState::event(StateMachineManager *smm)
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
                    smm->changeState(statesList::MainMenu);
                    break;
            }
        }
    }
}

void DeathState::render(StateMachineManager *smm, const float &interpolation)
{
    OverlayState::render(smm, interpolation);
    mRenderer.renderItem(mTitle);
    mRenderer.renderItem(mScoreCard);
    mRenderer.renderItem(mTip);
}

void DeathState::onPause()
{

}

void DeathState::onAwake()
{

}

void DeathState::update(StateMachineManager *smm)
{

}
