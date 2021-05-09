/**
 * @file ShootAtTargetNode.h
 * @brief A node for the enemy to fire towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#ifndef A2OOPGAME_SHOOTATTARGETNODE_H
#define A2OOPGAME_SHOOTATTARGETNODE_H

#include "ShootNode.h"
#include <glm.hpp>

/**
 * A node for the enemy to fire towards its target.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 08/05/2021]
 */
class ShootAtTargetNode : public ShootNode
{
public:
    explicit ShootAtTargetNode(BaseEnemy *enemy, const std::string &activateSound="../tmp/BeepOne.mp3", const std::string &shotSound="../sfx/shurikenThrow.mp3");
    ~ShootAtTargetNode() override = default;

    void onAwake() override;
    void onPause() override;

    void action(Ai *ai) override;
    void setConeSpread(float coneSpread);

protected:
    float mConeSpread;
};


#endif //A2OOPGAME_SHOOTATTARGETNODE_H
