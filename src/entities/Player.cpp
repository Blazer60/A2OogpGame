/**
 * @file Player.cpp.cc
 * @brief The main player class that the they can control.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "Player.h"

#include "GameState.h"
#include "BarrierCollider.h"

Player::Player(const glm::vec2 &position) :
        Entity(position,{ 32, 32 },{ 16, 16 },
               quad::layers::Player, "../tmp/Georb-0001.png"),
        mSpeed(25.f)
{
    mTransform.scale = glm::vec2 (4.f);
    mVelocity.x = mSpeed;
    mQueryLayers = quad::layers::EnemyProjectile | quad::layers::Enemy | quad::layers::Boundary;
}

void Player::update()
{
    const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    glm::vec2 axisInput(0);
    if (keys[SDL_SCANCODE_D]) { axisInput.x += 1; }
    if (keys[SDL_SCANCODE_A]) { axisInput.x -= 1; }
    if (keys[SDL_SCANCODE_W]) { axisInput.y -= 1; }
    if (keys[SDL_SCANCODE_S]) { axisInput.y += 1; }
    if (axisInput.x != 0 || axisInput.y != 0) { axisInput = glm::normalize(axisInput); }
    mVelocity = mSpeed * axisInput;

    mHitBoxColour = { 0, 0, 255, 255 };
    mTransform.position += mVelocity;
}

void Player::onCollision(const std::shared_ptr<Entity> &other)
{
    mHitBoxColour = { 255, 0, 0, 255 };
    // Check the type of the other and go from their.
    if (typeid(*other).hash_code() == typeid(BarrierCollider).hash_code())  // If the player hit a wall.
    {
        // Push back the player depending on the orientation of the wall they just hit.
        auto barrierCollider = std::dynamic_pointer_cast<BarrierCollider>(other);
        pushOffWall(barrierCollider);
    }
}
