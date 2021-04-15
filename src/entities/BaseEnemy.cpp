/**
 * @file BaseEnemy.cpp.cc
 * @brief The base entity class for all enemies.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize) :
    Entity(position, hitBoxSize)
{}

void BaseEnemy::update()
{

}

void BaseEnemy::onCollision(const Entity &other)
{

}
