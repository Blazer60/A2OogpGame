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

    /** Range in which to start tracking. */
    float mStartTrackingRange;

    /** Range in which to stop tracking */
    float mStopTrackingRange;

    /** How long the projectile should track for. */
    int mTrackingTime;

    /**
     * Used to stop tracking the target when the velocity
     * and direction are within this range.
     */
    float mConeAngle;

    glm::vec2 mAcceleration;
    float mMaxVelocity;
    glm::vec2 mForce;
};


#endif //A2OOPGAME_HEXEDPROJECTILE_H
