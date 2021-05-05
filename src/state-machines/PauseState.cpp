/**
 * @file PauseState.cpp.cc
 * @brief A state that can attach itself to another state allowing it to be paused.
 * Used when you still want the underlying state to be rendered.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 05/05/2021
 */


#include "PauseState.h"
#include "StateMachineManager.h"
#include "HudElement.h"
#include "HudImage.h"
#include "HudText.h"

#include <utility>

PauseState::PauseState(SDL_Renderer *renderer, const glm::ivec2 &windowSize, std::weak_ptr<StateMachine> attachedTo) :
        StateMachine(renderer, windowSize, statesList::Paused), mAttachedToState(std::move(attachedTo))
{
    mPauseIcon = std::make_shared<HudImage>(glm::ivec2(-32), HudElement::Center | HudElement::Middle, "../tmp/PauseIcon-0001.png");
    mPauseIcon->setScale(glm::vec2(4.f));
    mRenderer.loadImage(mPauseIcon->getImageRef());

    mPauseText = std::make_shared<HudText>(glm::ivec2(50, -50), HudElement::Bottom);
    mPauseText->setSize(20);
    mPauseText->setText("Press [esc] or [p] to unpause");
    mRenderer.loadText(mPauseText);
}

void PauseState::onPause()
{

}

void PauseState::onAwake()
{

}

void PauseState::event(StateMachineManager *smm)
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
                case SDLK_p:
                    if (auto state = mAttachedToState.lock()) { smm->changeState(state->getStateKey()); }
                    break;
            }
        }
    }
}

void PauseState::update(StateMachineManager *smm)
{

}

void PauseState::render(StateMachineManager *smm, const float &interpolation)
{
    mRenderer.update(interpolation);
    if (auto state = mAttachedToState.lock())
    {
        state->render(smm, 0);
    }

    mRenderer.renderItem(mPauseIcon);
    mRenderer.renderItem(mPauseText);
}
