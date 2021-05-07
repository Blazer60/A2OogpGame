/**
 * @file HexedProjectile.h
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_HEXEDPROJECTILE_H
#define A2OOPGAME_HEXEDPROJECTILE_H

#include "TrackingProjectile.h"

/**
 * A projectile that 'archs' towards the player
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class HexedProjectile : public TrackingProjectile
{
public:
    HexedProjectile(const glm::vec2 &position, const glm::vec2 &velocity, const size_t &collisionLayer);

    ~HexedProjectile() override = default;

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

protected:
    bool mIsTracking;
    float mStartTrackingRange;
    float mStopTrackingRange;
    int mTrackingTime;
    glm::vec2 mAcceleration;
    float mMaxVelocity;
    float mConeAngle;
    glm::vec2 mForce;
};


#endif //A2OOPGAME_HEXEDPROJECTILE_H
