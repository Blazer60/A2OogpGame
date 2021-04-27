/**
 * @file Entity.cpp.cc
 * @brief The base entity class for every object that is rendered to the screen.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "Entity.h"
#include "QuadTreeHelpers.h"

#include <iostream>
#include <utility>

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
    mIsCollidable(true),
    mIsRenderable(true),
    mAngularVelocity(0)
{
    if (mImageRef.empty()) { mIsRenderable = false; }
}

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
        mIsCollidable(true),
        mIsRenderable(true),
        mAngularVelocity(0)
{

}

// Entity with image only. It will not be added to the tree.
Entity::Entity(const glm::vec2 &position, const glm::vec2 &imageSize, std::string imageRef) :
    mTransform(position, 0.0, imageSize),
    mHitBoxSize(0.f),
    mImageRef(std::move(imageRef)),
    mVelocity(0.f),
    mHitBoxOffset(0.f),
    mHitBoxColour({0, 0, 255, 255}),
    mCollisionLayer(0),
    mIsDead(false),
    mIsCollidable(false),
    mIsRenderable(true),
    mAngularVelocity(0)
{

}

quad::rect Entity::getHitBoxRect() const
{
    return { mTransform.position + mHitBoxOffset, mHitBoxSize };
}
