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

Player::Player(const glm::vec2 &position) :
        Entity(position,{ 16, 16 },{ 32, 32 },
               quad::layers::Player, "../tmp/Georb-0001.png"),
        mSpeed(50.f)
{
    mTransform.scale = glm::vec2 (4.f);
    mVelocity.x = mSpeed;
}

void Player::event(const inputs &keysPressed)
{
    glm::vec2 axisInput(0);
    if (keysPressed.right) { axisInput.x += 1; }
    if (keysPressed.left) { axisInput.x -= 1; }
    if (keysPressed.up) { axisInput.y -= 1; }
    if (keysPressed.down) { axisInput.y += 1; }
    if (axisInput.x != 0 || axisInput.y != 0) { axisInput = glm::normalize(axisInput); }
    mVelocity = mSpeed * axisInput;
}

void Player::update()
{
    mHitBoxColour = { 0, 0, 255, 255 };
    mTransform.position += mVelocity;
}

void Player::onCollision(const std::shared_ptr<Entity> &other)
{
    mHitBoxColour = { 255, 0, 0, 255 };
}
