/**
 * @file OverlayState.cpp.cc
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 05/05/2021
 */


#include "OverlayState.h"

#include <utility>
#include "StateMachineManager.h"

OverlayState::OverlayState(SDL_Renderer *renderer, const glm::ivec2 &windowSize,
                           std::weak_ptr<StateMachine> attachToState, char stateKey) :
    StateMachine(renderer, windowSize, stateKey), mAttachedToState(std::move(attachToState))
{}

void OverlayState::event(StateMachineManager *smm)
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

void OverlayState::render(StateMachineManager *smm, const float &interpolation)
{
    mRenderer.update(interpolation);
    if (auto state = mAttachedToState.lock())
    {
        state->render(smm, 0);
    }
}
