/**
 * @file HexedProjectile.cpp.cc
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "HexedProjectile.h"

HexedProjectile::HexedProjectile(const glm::vec2 &position, const glm::vec2 &velocity, const size_t &collisionLayer)
        : TrackingProjectile(position, velocity, collisionLayer,"assets/images/HexedProjectile-0001.png"),
          mIsTracking(false), mStartTrackingRange(600.f), mStopTrackingRange(150.f), mTrackingTime(300),  // 10 Seconds
          mAcceleration(0.f), mForce(2.f), mMaxVelocity(25.f), mConeAngle(0.9)

{}

void HexedProjectile::update()
{
    mTrackingTime--;
    if (mTrackingTime > 0)
    {
        // Toggle Tracking on or off depending on the distance.
        if (mIsTracking)    { mIsTracking = getTrackedDistance() > mStopTrackingRange; }
        else                { mIsTracking = getTrackedDistance() > mStartTrackingRange; }
    }
    else
    {
        // Don't ever track after a set amount of time.
        mIsTracking = false;
    }
    if (glm::dot(getTrackedDirection(), glm::normalize(mVelocity)) > mConeAngle)
    {
        mIsTracking = false;
    }

    mAngularVelocity = 0.0;
    // Start moving the towards the tracked target.
    if (mIsTracking)
    {
        mAngularVelocity = 50.0;
        glm::vec2 direction = getTrackedDirection();
        mAcceleration.x = direction.x > 0 ? mForce.x : -mForce.x;
        mAcceleration.y = direction.y > 0 ? mForce.y : -mForce.y;
    }
    mVelocity += mAcceleration;
    clampVelocity(mMaxVelocity);
    TrackingProjectile::update();
}

void HexedProjectile::onCollision(const std::shared_ptr<Entity> &other)
{
    TrackingProjectile::onCollision(other);
}
