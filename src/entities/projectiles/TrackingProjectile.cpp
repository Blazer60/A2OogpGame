/**
 * @file TrackingProjectile.cpp.cc
 * @brief A projectile that can track where an entity is.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "TrackingProjectile.h"

#include <utility>

TrackingProjectile::TrackingProjectile(const glm::vec2 &position, const glm::vec2 &velocity,
                                       const size_t &collisionLayer, const std::string &imageRef) :
                                            BaseProjectile(position, velocity, collisionLayer, imageRef)
{}

void TrackingProjectile::update()
{
    BaseProjectile::update();
}

void TrackingProjectile::onCollision(const std::shared_ptr<Entity> &other)
{
    BaseProjectile::onCollision(other);
}

void TrackingProjectile::setTrackedEntity(std::weak_ptr<Entity> newTrackedEntity)
{
    mTrackedEntity = std::move(newTrackedEntity);
}

float TrackingProjectile::getTrackedDistance()
{
    float distance = 0;
    if (auto trackedEntity = mTrackedEntity.lock())
    {
        distance = glm::distance(mTransform.position, trackedEntity->mTransform.position);
    }
    return distance;
}

glm::vec2 TrackingProjectile::getTrackedDirection()
{
    glm::vec2 direction(0.f);
    if (auto trackedEntity = mTrackedEntity.lock())
    {
        direction = glm::normalize(trackedEntity->mTransform.position - mTransform.position);
    }
    return direction;
}
