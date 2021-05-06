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
#include "OverlayState.h"

#include <utility>

PauseState::PauseState(SDL_Renderer *renderer, const glm::ivec2 &windowSize, std::weak_ptr<StateMachine> attachedTo,
                       float volumePercentage) :
        OverlayState(renderer, windowSize, std::move(attachedTo) ,statesList::Paused),
        mPauseSound("../tmp/Tone1.mp3"), mUnPauseSound("../tmp/Tone2.mp3")
{
    mPauseIcon = std::make_shared<HudImage>(glm::ivec2(-32), HudElement::Center | HudElement::Middle, "../tmp/PauseIcon-0001.png");
    mPauseIcon->setScale(glm::vec2(4.f));
    mRenderer.loadImage(mPauseIcon->getImageRef());

    mPauseText = std::make_shared<HudText>(glm::ivec2(50, -50), HudElement::Bottom);
    mPauseText->setSize(20);
    mPauseText->setText("Press [esc] to quit or [p] to unpause");
    mRenderer.loadText(mPauseText);

    mVolumeText = std::make_shared<HudText>(glm::ivec2(-614, -50), HudElement::Bottom | HudElement::Right);
    mVolumeText->setSize(20);
    mVolumeText->setText("[m] Increase Volume | [n] Decrease Volume (" + std::to_string(static_cast<int>(volumePercentage * 100)) + ")");
    mRenderer.loadText(mVolumeText);

    mPauseSound.play();
}

void PauseState::onPause()
{
    mUnPauseSound.play();  // Yes this is backwards.
}

void PauseState::onAwake()
{
    mPauseSound.play();  // Yes this is backwards.
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
                    smm->changeState(statesList::MainMenu);
                    break;
                case SDLK_p:
                    if (auto state = mAttachedToState.lock()) { smm->changeState(state->getStateKey()); }
                    break;
                case SDLK_m:
                    smm->setVolume(soundChannel::Master, 0.01f, true);
                    updateVolumeText(smm);
                    break;
                case SDLK_n:
                    smm->setVolume(soundChannel::Master, -0.01f, true);
                    updateVolumeText(smm);
                    break;
            }
        }
    }
}

void PauseState::updateVolumeText(StateMachineManager *smm)
{
    float volume = smm->getVolume(soundChannel::Master) * 100.f;
    mVolumeText->setText("[m] Increase Volume | [n] Decrease Volume (" + std::to_string(static_cast<int>(volume)) + ")");
}

void PauseState::update(StateMachineManager *smm)
{
}

void PauseState::render(StateMachineManager *smm, const float &interpolation)
{
    OverlayState::render(smm, interpolation);

    mRenderer.renderItem(mPauseIcon);
    mRenderer.renderItem(mPauseText);
    mRenderer.renderItem(mVolumeText);
}
