/**
 * @file ChargeNode.h
 * @brief A node that makes mecha chad charge towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#ifndef A2OOPGAME_CHARGENODE_H
#define A2OOPGAME_CHARGENODE_H

#include "Node.h"

/**
 * A node that makes mecha chad charge towards its target.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 08/05/2021]
 */
class ChargeNode : public Node
{
public:
    explicit ChargeNode(MechaChad *mechaChad);
    ~ChargeNode() override = default;

    void onAwake() override;
    void onPause() override;

    void action(Ai *ai) override;

protected:
    float mSpeed;
    float mMaxSpeed;
    float mSpeedMultiplier;
};


#endif //A2OOPGAME_CHARGENODE_H
