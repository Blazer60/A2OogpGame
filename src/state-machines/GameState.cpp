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
#include "BaseEnemy.h"
#include "HelperFunctions.h"

#include <iostream>

#if DEBUG_DRAW_HIT_BOXES  // Used to draw the quadtree to the screen. Not seen in release mode.
#include <mutex>
std::mutex mtx;  // Used to stop race conditions on Quad Tree (that should only be accessed by update functions).
#endif

GameState::GameState(SDL_Window *window) :
    StateMachine(window),
    mPlayer(std::make_shared<Player>(glm::vec2{ 50.f, 50.f }, glm::vec2{ 320.f, 240.f }))
{
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(400, 500), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(900, -100), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(000, 700), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(300, 700), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(600, 700), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(900, 700), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(1200, 700), glm::vec2(320.f, 240.f)));
    mEntities.emplace_back(std::make_shared<BaseEnemy>(glm::vec2(1500, 700), glm::vec2(320.f, 240.f)));

    mRenderer.setTarget(mPlayer);
}

void GameState::onPause()
{

}

void GameState::onAwake()
{

}

void GameState::update(StateMachineManager *smm)
{
#if DEBUG_DRAW_HIT_BOXES
    mtx.lock();
#endif
    mQuadTree = std::make_unique<entityTree>(quad::rect{ -1920, -1080, 3840, 2160 }, 1);
    mQuadTree->insert(mPlayer, quad::rect{ mPlayer->mTransform.position, mPlayer->mHitBoxSize });

    for (auto &item : mEntities)
    {
        mQuadTree->insert(item, quad::rect{ item->mTransform.position, item->mHitBoxSize });
    }
#if DEBUG_DRAW_HIT_BOXES
    mtx.unlock();
#endif

    mPlayer->event(mInputs);
    mPlayer->update();

    for (auto &item : mEntities)
    {
        item->update();
    }

    // Updated Collision
    std::vector<std::shared_ptr<Entity>> collidedWith = mQuadTree->getIntersecting(quad::rect{mPlayer->mTransform.position, mPlayer->mHitBoxSize});
    for (auto &other : collidedWith)
    {
        if (other == mPlayer) { continue; }
        mPlayer->onCollision(other);
        other->onCollision(mPlayer);
    }
}

void GameState::render(StateMachineManager *smm, const float &interpolation)
{
    // Items are ordered from back to front.
    mRenderer.update(interpolation);  // Must be at the start of rendering

    for (auto &item : mEntities)
    {
        mRenderer.renderItem(item);
    }

    mRenderer.renderItem(mPlayer);

#if DEBUG_DRAW_HIT_BOXES  // Set in CMakeLists.txt
    for (auto &item : mEntities)
    {
        mRenderer.renderHitBox(item);
    }

    mRenderer.renderHitBox(mPlayer);

    mtx.lock();
    mQuadTree->debugRender(&mRenderer);
    mtx.unlock();
#endif

    mRenderer.flip();  // Must be at the end of rendering.
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
