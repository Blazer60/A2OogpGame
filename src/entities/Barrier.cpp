/**
 * @file Barrier.cpp.cc
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#include "Barrier.h"
#include "QuadTreeHelpers.h"

Barrier::Barrier(const glm::vec2 &position) :
    Entity(position, glm::vec2(4096), quad::layers::Boundary, "../tmp/Walls-0001.png")
{
    mTransform.scale = glm::vec2(4.f);
}

void Barrier::update()
{

}

void Barrier::onCollision(const std::shared_ptr<Entity> &other)
{

}
