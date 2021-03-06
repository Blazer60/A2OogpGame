/**
 * @file MenuState.cpp.cc
 * @brief The first state that is loaded when the game is created.
 * Allows the user to play the game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "MenuState.h"
#include "StateMachineManager.h"
#include "HudText.h"

MenuState::MenuState(SDL_Renderer *renderer, const glm::ivec2 &windowSize, float volumePercentage) :
    StateMachine(renderer, windowSize, statesList::MainMenu),
    mTextYAdvance(20), mTextYPos(10), mSize(20), mMusic("assets/music/TitleScreen.mp3"),
    mTitleFlashRate(30), mTitleFlashTimer(0)
{
    // Setting up the title.
    mTitle = std::make_shared<HudText>(glm::ivec2(-150, -20), HudElement::Center | HudElement::Middle);
    mTitle->setText("Press P to Play");
    mRenderer.loadText(mTitle);

    // Setting up more info.
    addText("Controls:");
    addText("Move   - wasd");
    addText("Dodge  - wasd + space or space");
    addText("Pause  - p");
    mTextYPos += mTextYAdvance;
    addText("Objective:");
    addText("Survive for as long as possible.");

    // Music volume setup.
    mVolumeText = std::make_shared<HudText>(glm::ivec2(-614, -50), HudElement::Bottom | HudElement::Right);
    mVolumeText->setSize(20);
    mVolumeText->setText("[m] Increase Volume | [n] Decrease Volume (" + std::to_string(static_cast<int>(volumePercentage * 100.f)) + ")");
    mRenderer.loadText(mVolumeText);

    mMusic.play(true);
}

void MenuState::onPause()
{}

void MenuState::onAwake()
{
    mMusic.play(true);
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
                case SDLK_m:
                    smm->setVolume(soundChannel::Master, 0.01f, true);
                    break;
                case SDLK_n:
                    smm->setVolume(soundChannel::Master, -0.01f, true);
                    break;
            }
        }
    }

    const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_P]) { smm->changeState(statesList::InGame); }
}

void MenuState::update(StateMachineManager *smm)
{
    updateVolumeText(smm);

    // Flashing the title
    mTitleFlashTimer++;
    if (mTitleFlashTimer >= mTitleFlashRate)
    {
        mTitle->setVisibility(!mTitle->isVisible());
        mTitleFlashTimer = 0;
    }
}

void MenuState::render(StateMachineManager *smm, const float &interpolation)
{
    mRenderer.update(interpolation);

    mRenderer.renderItem(mTitle);
    mRenderer.renderItem(mVolumeText);

    for (auto &item : mTexts)
    {
        mRenderer.renderItem(item);
    }
}

void MenuState::updateVolumeText(StateMachineManager *smm)
{
    float volume = smm->getVolume(soundChannel::Master) * 100.f;
    mVolumeText->setText("[m] Increase Volume | [n] Decrease Volume (" + std::to_string(static_cast<int>(volume)) + ")");
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
