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
    mTransform(position, 0.0, glm::vec2(1.f, 1.f)),
    mHitBoxSize(hitBoxSize),
    mImageRef(std::move(imageRef)),
    mVelocity({ 0.f, 0.f }),
    mHitBoxColour({ 0, 0, 255, 255 }),
    mCollisionLayer(collisionLayer),
    mHitBoxOffset(0.f),
    mIsDead(false),
    mAngularVelocity(0)
{}

Entity::Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const glm::vec2 &hitBoxOffSet,
               const size_t &collisionLayer, std::string  imageRef) :
        mTransform(position, 0.0, glm::vec2(1.f, 1.f)),
        mHitBoxSize(hitBoxSize),
        mImageRef(std::move(imageRef)),
        mVelocity({ 0.f, 0.f }),
        mHitBoxOffset(hitBoxOffSet),
        mHitBoxColour({0, 0, 255, 255}),
        mCollisionLayer(collisionLayer),
        mIsDead(false),
        mAngularVelocity(0)
{

}

quad::rect Entity::getHitBoxRect() const
{
    return { mTransform.position + mHitBoxOffset, mHitBoxSize };
}
