/**
 * @file ShootNode.h
 * @brief Holds basic information for an AI to shoot.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 09/05/2021
 */


#ifndef A2OOPGAME_SHOOTNODE_H
#define A2OOPGAME_SHOOTNODE_H

#include "Node.h"
#include "SoundFx.h"

#include <glm.hpp>

/**
 * Holds basic information for an AI to shoot.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 09/05/2021]
 */
class ShootNode : public Node
{
public:
    explicit ShootNode(BaseEnemy *enemy, const std::string &activateSound, const std::string &shotSound);
    ~ShootNode() override = default;

    void setProjectileType(char type);
    void setProjectileVelocity(glm::vec2 velocity);
    void setAmountOfProjectiles(int amountOfProjectiles);
    void setProjectileCountIncrease(int count);

protected:
    /** The sound that is played when a projectile is spawned. */
    SoundFx mShootSound;

    int mAmountOfProjectiles;
    glm::vec2 mProjectileSpawnVelocity;
    char mProjectileType;

    /** How many more projectiles should be fired the next time this node is activated. */
    int mProjectileCountIncrease;
};


#endif //A2OOPGAME_SHOOTNODE_H
