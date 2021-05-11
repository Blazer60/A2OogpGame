/**
 * @file TrackingProjectile.h
 * @brief A projectile that can track where an entity is.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_TRACKINGPROJECTILE_H
#define A2OOPGAME_TRACKINGPROJECTILE_H

#include "BaseProjectile.h"

#include <memory>

/**
 * A projectile that can track where an entity is.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class TrackingProjectile : public BaseProjectile
{
public:
    TrackingProjectile(const glm::vec2 &position, const glm::vec2 &velocity, const size_t &collisionLayer,
                       const std::string &imageRef);
    ~TrackingProjectile() override = default;

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

    void setTrackedEntity(std::weak_ptr<Entity> newTrackedEntity);

protected:
    float getTrackedDistance();
    glm::vec2 getTrackedDirection();

    std::weak_ptr<Entity> mTrackedEntity;
};


#endif //A2OOPGAME_TRACKINGPROJECTILE_H
