/**
 * @file Player.cpp.cc
 * @brief The main player class that the they can control.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "Player.h"

Player::Player(const glm::vec2 &position, const glm::vec2 &hitBoxSize) :
    Entity(position, hitBoxSize), mSpeed(50.f)
{}

void Player::update(float deltaTime)
{
    mTransform.position.x += mSpeed * deltaTime;
}

void Player::onCollision(const Entity &other)
{

}
