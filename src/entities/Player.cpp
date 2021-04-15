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

Player::Player(const glm::vec2 &position, const glm::vec2 &hitBoxSize) :
    Entity(position, hitBoxSize), mSpeed(5.f)
{
    mVelocity.x = mSpeed;
}

void Player::event(const keys &keysPressed)
{
    glm::vec2 axisInput(0);
    if (keysPressed.right) { axisInput.x += 1; }
    if (keysPressed.left) { axisInput.x -= 1; }
    if (keysPressed.up) { axisInput.y -= 1; }
    if (keysPressed.down) { axisInput.y += 1; }
    glm::normalize(axisInput);
    mVelocity = mSpeed * axisInput;
}

void Player::update()
{
    mTransform.position += mVelocity;
}

void Player::onCollision(const Entity &other)
{

}