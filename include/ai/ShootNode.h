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
    explicit ShootNode(MechaChad *mechaChad, const std::string &soundPath);
    ~ShootNode() override = default;

protected:
    SoundFx mShootSound;

    int mAmountOfProjectiles;
    glm::vec2 mProjectileSpawnVelocity;
    char mProjectileType;
};


#endif //A2OOPGAME_SHOOTNODE_H