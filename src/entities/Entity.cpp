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
#include "BarrierCollider.h"

#include <iostream>
#include <utility>

Entity::Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const size_t &collisionLayer,
               std::string imageRef) :
    mTransform(position, 0.0, glm::vec2(1.f, 1.f)), mHitBoxSize(hitBoxSize), mImageRef(std::move(imageRef)),
    mVelocity({ 0.f, 0.f }), mHitBoxColour({ 0, 0, 255, 255 }), mCollisionLayer(collisionLayer),
    mHitBoxOffset(0.f), mIsDead(false), mIsCollidable(true), mIsRenderable(true), mAngularVelocity(0),
    mQueryLayers(0)
{
    if (mImageRef.empty()) { mIsRenderable = false; }
}

Entity::Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const glm::vec2 &hitBoxOffSet,
               const size_t &collisionLayer, std::string  imageRef) :
    mTransform(position, 0.0, glm::vec2(1.f, 1.f)), mHitBoxSize(hitBoxSize), mImageRef(std::move(imageRef)),
    mVelocity({ 0.f, 0.f }), mHitBoxOffset(hitBoxOffSet), mHitBoxColour({0, 0, 255, 255}),
    mCollisionLayer(collisionLayer), mIsDead(false), mIsCollidable(true), mIsRenderable(true), mAngularVelocity(0),
    mQueryLayers(0)
{}

// Entity with image only. It will not be added to the quad tree.
Entity::Entity(const glm::vec2 &position, const glm::vec2 &imageSize, std::string imageRef) :
    mTransform(position, 0.0, imageSize), mHitBoxSize(0.f), mImageRef(std::move(imageRef)),
    mVelocity(0.f), mHitBoxOffset(0.f), mHitBoxColour({0, 0, 255, 255}), mCollisionLayer(0), mIsDead(false),
    mIsCollidable(false), mIsRenderable(true), mAngularVelocity(0), mQueryLayers(0)
{}

quad::rect Entity::getHitBoxRect() const
{
    return { mTransform.position + mHitBoxOffset, mHitBoxSize };
}

glm::vec2 Entity::getHitBoxCenter() const
{
    return mTransform.position + mHitBoxOffset + (mHitBoxSize / 2.f);
}

void Entity::pushOffWall(const std::shared_ptr<BarrierCollider> &barrierCollider)
{
    glm::vec2 pushBackDirection(0);
    switch (barrierCollider->mDirectionFacing)
    {
        case BarrierCollider::NorthFacing:
            pushBackDirection.y = barrierCollider->mTransform.position.y - (mHitBoxSize.y + mHitBoxOffset.y);
            pushBackDirection.x = mTransform.position.x;
            break;
        case BarrierCollider::EastFacing:
            pushBackDirection.x = barrierCollider->mTransform.position.x + barrierCollider->mHitBoxSize.x;
            pushBackDirection.y = mTransform.position.y;
            break;
        case BarrierCollider::SouthFacing:
            pushBackDirection.y = barrierCollider->mTransform.position.y + barrierCollider->mHitBoxSize.y;
            pushBackDirection.x = mTransform.position.x;
            break;
        default:
            pushBackDirection.x = barrierCollider->mTransform.position.x - (mHitBoxSize.x + mHitBoxOffset.x);
            pushBackDirection.y = mTransform.position.y;
            break;
    }
    mTransform.position = pushBackDirection;
    mVelocity = glm::vec2(0);  // Prevents the camera from trying to guess where the entity will be.
}
