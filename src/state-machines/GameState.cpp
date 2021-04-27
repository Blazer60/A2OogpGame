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
#include "BaseProjectile.h"
#include "HelperFunctions.h"
#include "MechaChad.h"
#include "BarrierImage.h"
#include "BarrierCollider.h"

#include <iostream>

GameState::GameState(SDL_Window *window) :
    StateMachine(window),
    mPlayer(std::make_shared<Player>(glm::vec2{ 50.f, 50.f }))
{
    mEntities.reserve(1000);
    mEntities.emplace_back(std::make_shared<BarrierImage>(glm::vec2(-2048, -2048)));
    mEntities.emplace_back(std::make_shared<BarrierCollider>(glm::vec2(-2048, -2048), BarrierCollider::EastFacing));
    mEntities.emplace_back(std::make_shared<BarrierCollider>(glm::vec2(1920, -2048), BarrierCollider::WestFacing));
    mEntities.emplace_back(std::make_shared<BarrierCollider>(glm::vec2(-1920, -2048), BarrierCollider::SouthFacing));
    mEntities.emplace_back(std::make_shared<BarrierCollider>(glm::vec2(-1920, 1920), BarrierCollider::NorthFacing));
    mEntities.emplace_back(std::make_shared<MechaChad>(glm::vec2(0, 0), this, std::weak_ptr<Entity>(mPlayer)));
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
    mQuadTree = std::make_unique<entityTree>(quad::rect{ -2098, -2098, 4146, 4146 }, 10);
    mQuadTree->insert(mPlayer, mPlayer->getHitBoxRect(), mPlayer->mCollisionLayer);

    for (auto &item : mEntities)
    {
        if (item->mIsCollidable) { mQuadTree->insert(item, item->getHitBoxRect(), item->mCollisionLayer); }
    }

    mPlayer->event(mInputs);
    mPlayer->update();

    for (auto &item : mEntities)
    {
        item->update();
    }

    collisionUpdateCheck();     // Check collisions between all entities.
    cleanEntities();            // Remove dead entities.
    moveBufferedEntities();     // Add Buffered Entities to main vector.

    static unsigned int loops = 0;
    loops++;
    if (loops > 30)
    {
        loops = 0;
        std::cout << mEntities.size() << std::endl;
    }
}

void GameState::render(StateMachineManager *smm, const float &interpolation)
{
    // Items are ordered from back to front.
    mRenderer.update(interpolation);  // Must be at the start of rendering

    for (std::shared_ptr<Entity>& item : mEntities)
    {
        mRenderer.renderItem(item);
    }

    mRenderer.renderItem(mPlayer);

#if DEBUG_DRAW_HIT_BOXES  // Set in CMakeLists.txt
    for (const auto &item : mEntities)
    {
        mRenderer.renderHitBox(item);
    }

    mRenderer.renderHitBox(mPlayer);

    if (mQuadTree) { mQuadTree->debugRender(&mRenderer); }
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

void GameState::createEntity(const std::shared_ptr<Entity>& entity)
{
    mBufferedEntities.push_back(entity);
}

void GameState::moveBufferedEntities()
{
    for (auto &item : mBufferedEntities)
    {
        mEntities.push_back(item);
    }
    mBufferedEntities.clear();
}

void GameState::cleanEntities()
{
    for (int i = static_cast<int>(mEntities.size() ) - 1; i >= 0; --i)
    {
        if (mEntities[i]->mIsDead)
        {
            std::swap(mEntities[i], mEntities[mEntities.size() - 1]);
            mEntities.pop_back();
        }
    }
}

void GameState::collisionUpdateCheck()
{
    // Handle player collision
    auto playerCollisions = mQuadTree->getIntersecting(mPlayer->getHitBoxRect(), mPlayer->mQueryLayers);
    for (auto &other : playerCollisions)
    {
        mPlayer->onCollision(other);
    }

    // Handle all other entities collision.
    for (auto &currentEntity : mEntities)
    {
        if (!currentEntity->mIsCollidable) { continue; }  // No need to check if the entity has no hit box.

        auto otherEntities = mQuadTree->getIntersecting(currentEntity->getHitBoxRect(), currentEntity->mQueryLayers);
        for (auto &other : otherEntities)
        {
            if (currentEntity == other) { continue; }  // Entities could collide with themself.
            currentEntity->onCollision(other);
        }
    }
}
