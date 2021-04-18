/**
 * @file Entity.cpp.cc
 * @brief The base entity class for every object that is rendered to the screen.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "Entity.h"
#include <utility>

#include "QuadTreeHelpers.h"

Entity::Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const size_t &collisionLayer,
               std::string imageRef) :
    mTransform(position, 0.f, glm::vec2(1.f, 1.f)),
    mHitBoxSize(hitBoxSize),
    mImageRef(std::move(imageRef)),
    mVelocity({ 0.f, 0.f }),
    mHitBoxColour({ 0, 0, 255, 255 }),
    mCollisionLayer(collisionLayer)
{}

quad::rect Entity::getRect()
{
    return quad::rect(mTransform.position, mHitBoxSize);
}
