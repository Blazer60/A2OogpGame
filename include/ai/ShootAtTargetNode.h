/**
 * @file ShootAtTargetNode.h
 * @brief A node for the mecha chad to fire towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#ifndef A2OOPGAME_SHOOTATTARGETNODE_H
#define A2OOPGAME_SHOOTATTARGETNODE_H

#include "Node.h"
#include <glm.hpp>

class MechaChad;

/**
 * A node for the mecha chad to fire towards its target.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 08/05/2021]
 */
class ShootAtTargetNode : public Node
{
public:
    explicit ShootAtTargetNode(MechaChad* mechaChad);
    ~ShootAtTargetNode() override = default;

    void onAwake() override;
    void onPause() override;

    void action(Ai *ai) override;

protected:
    SoundFx mShootSound;

    int mAmountOfProjectiles;
    float mConeSpread;
    glm::vec2 mProjectileSpawnVelocity;
    char mProjectileType;
};


#endif //A2OOPGAME_SHOOTATTARGETNODE_H
