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
              const size_t &collisionLayer = quad::layers::Enemy);

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

protected:
    static std::vector<glm::vec2> getUnitCirclePoints(unsigned int n, const float &offSet);

    GameState *mGame;
    std::weak_ptr<Entity> mTargetEntity;
    std::shared_ptr<BaseProjectile> mProjectiles;
};


#endif //A2OOPGAME_BASEENEMY_H
