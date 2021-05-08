/**
 * @file ShootInCircleNode.h
 * @brief Lets mecha chad shoot projectiles in a circle.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#ifndef A2OOPGAME_SHOOTINCIRCLENODE_H
#define A2OOPGAME_SHOOTINCIRCLENODE_H

#include "Node.h"
#include "SoundFx.h"

class MechaChad;

/**
 * Lets mecha chad shoot projectiles in a circle.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 08/05/2021]
 */
class ShootInCircleNode : public Node
{
public:
    explicit ShootInCircleNode(MechaChad *mechaChad);
    ~ShootInCircleNode() override = default;

    void onAwake() override;
    void onPause() override;

    void action(Ai *ai) override;

protected:
    SoundFx mFireSound;

    int mAmountOfProjectiles;
    float mOffSet;
};


#endif //A2OOPGAME_SHOOTINCIRCLENODE_H
