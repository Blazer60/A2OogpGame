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
#include "SoundFx.h"
#include "Ai.h"


#include <memory>
#include <vector>
#include <glm.hpp>

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
    ~BaseEnemy() override = default;

    /**
     * Spawns a projectile in the attached state.
     * @param projectile The projectile you want to move to the game state.
     */
    void createProjectile(std::shared_ptr<BaseProjectile> projectile);

    /**
     * Spawns a projectile in the attached state.
     * @see BaseProjectile.h projectiles
     * @param velocity How fast is the projectile
     * @param type The type of projectile (use projectiles::type)
     */
    void createProjectile(const glm::vec2 &velocity, char type);

    glm::vec2 getTargetDirection();

protected:
    GameState *mGame;
    std::weak_ptr<Entity> mTargetEntity;
};


#endif //A2OOPGAME_BASEENEMY_H
