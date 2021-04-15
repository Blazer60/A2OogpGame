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

/**
 * The base entity class for all enemies.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class BaseEnemy :  public Entity
{
public:
    BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize);

    void update() override;
    void onCollision(const Entity &other) override;
};


#endif //A2OOPGAME_BASEENEMY_H
