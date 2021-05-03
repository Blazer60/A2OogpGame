/**
 * @file BaseEnemy.h
 * @brief The base entity class for all enemies.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#ifndef A2OOPGAME_BASEENEMY_H
#define A2OOPGAME_BASEENEMY_H

#include "Entity.h"
#include "BaseProjectile.h"
#include "QuadTreeHelpers.h"


#include <memory>
#include <vector>

class GameState;

/**
 * The base entity class for all enemies.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class BaseEnemy :  public Entity
{
public:
    BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize, GameState *attachToState,
              std::weak_ptr<Entity> targetEntity, const size_t &collisionLayer = quad::layers::Enemy);

protected:
    /**
     * Gets evenly spaced vectors within a unit circle.
     * @param n The number of vectors that you want.
     * @param offSet The angle off of the horizontal plane (1, 0) (in degrees)
     * @returns n amount of points in a unit circle
     */
    static std::vector<glm::vec2> getUnitCirclePoints(unsigned int n, const float &offSet=0);

    /**
     * Gets unit vectors pointing towards a direction.
     * @param n The number of vectors that you want.
     * @param direction Where you want the centered vector to aim towards.
     * @param coneSpread How spread out you want the vectors (in degrees)
     * @returns n amount of points within the specified cone spread.
     */
    static std::vector<glm::vec2> getUnitConePoints(unsigned int n, const glm::vec2 &direction, float coneSpread=20.f);

    GameState *mGame;
    std::weak_ptr<Entity> mTargetEntity;
};


#endif //A2OOPGAME_BASEENEMY_H
