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
#include "Music.h"
#include "Timer.h"
#include "HudText.h"
#include "LifeGauge.h"
#include "QuadTree.h"
#include "Player.h"

#include <iostream>

GameState::GameState(SDL_Renderer *renderer, const glm::ivec2 &windowSize) :
        StateMachine(renderer, windowSize),
    mPlayer(std::make_shared<Player>(glm::vec2{ -400.f, 50.f })),
    mMusic(std::make_unique<Music>("../tmp/FeelThePower.mp3"))
{
    mRenderer.loadImage(mPlayer->mImageRef);
    mEntities.reserve(1000);
    createEntity(std::make_shared<BarrierImage>(glm::vec2(-2048, -2048)));
    createEntity(std::make_shared<BarrierCollider>(glm::vec2(-2048, -2048), BarrierCollider::EastFacing));
    createEntity(std::make_shared<BarrierCollider>(glm::vec2(1920, -2048), BarrierCollider::WestFacing));
    createEntity(std::make_shared<BarrierCollider>(glm::vec2(-1920, -2048), BarrierCollider::SouthFacing));
    createEntity(std::make_shared<BarrierCollider>(glm::vec2(-1920, 1920), BarrierCollider::NorthFacing));
    createEntity(std::make_shared<MechaChad>(glm::vec2(0, 0), this, std::weak_ptr<Entity>(mPlayer)));

    createHudText(std::make_shared<Timer>(glm::ivec2(-80, -100), HudElement::Bottom | HudElement::Middle));

    mLifeGauge = std::make_shared<LifeGauge>(glm::ivec2(-48, -140), HudElement::Bottom | HudElement::Middle);
    mRenderer.loadImage(mLifeGauge->getImageRef());
    mRenderer.setTarget(mPlayer);
    mMusic->play();
}

void GameState::onPause()
{
}

void GameState::onAwake()
{

}

void GameState::update(StateMachineManager *smm)
{
    mPlayer->update();
    for (auto &item : mEntities) { item->update(); }
    for (auto &item : mHudTexts) { item->update(); }

    collisionUpdateCheck();     // Check collisions between all entities.
    cleanEntities();            // Remove dead entities.
    moveBufferedEntities();     // Add Buffered Entities to main vector.
    if (mPlayer->getLives() <= 0) { smm->changeState(statesList::MainMenu); }
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

    mRenderer.renderItem(mLifeGauge);

    for (auto &text : mHudTexts)
    {
        mRenderer.renderItem(text);
    }

    mRenderer.flip();  // Must be at the end of rendering.
}

void GameState::createEntity(const std::shared_ptr<Entity>& entity)
{
    mBufferedEntities.push_back(entity);
    mRenderer.loadImage(entity->mImageRef);
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
            mRenderer.freeImage(mEntities[i]->mImageRef);
            std::swap(mEntities[i], mEntities[mEntities.size() - 1]);
            mEntities.pop_back();
        }
    }
}

void GameState::collisionUpdateCheck()
{
    // Create the collision tree
    mQuadTree = std::make_unique<entityTree>(quad::rect{ -2098, -2098, 4146, 4146 }, 10);
    mQuadTree->insert(mPlayer, mPlayer->getHitBoxRect(), mPlayer->mCollisionLayer);

    for (auto &item : mEntities)
    {
        if (item->mIsCollidable) { mQuadTree->insert(item, item->getHitBoxRect(), item->mCollisionLayer); }
    }

    // Start handling all of the collisions.

    // Handle all entities collision.
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

    // Handle player collision - done last since a projectile hit can set i-frames for the player.
    auto playerCollisions = mQuadTree->getIntersecting(mPlayer->getHitBoxRect(), mPlayer->mQueryLayers);
    for (auto &other : playerCollisions)
    {
        mPlayer->onCollision(other);

        // Check to see if we have to update the life gauge.
        if (mPlayer->getLives() != mLifeGauge->getCurrentRefNumber() && mPlayer->getLives() >= 0)
        {
            mRenderer.freeImage(mLifeGauge->getImageRef());
            mLifeGauge->setImageRef(mPlayer->getLives());
            mRenderer.loadImage(mLifeGauge->getImageRef());
        }
    }
}

void GameState::createHudText(std::shared_ptr<HudText> text)
{
    mHudTexts.push_back(text);
    mRenderer.loadText(text);
}

void GameState::event(StateMachineManager *smm)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) { smm->mIsRunning = false; }
    }

    // This method can sometimes not recognise when something was inputted by the user.
    const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_ESCAPE]) { smm->changeState(statesList::MainMenu); }
}

