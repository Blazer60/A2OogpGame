/**
 * @file ShootInCircleNode.h
 * @brief Lets an enemy shoot projectiles in a circle.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#ifndef A2OOPGAME_SHOOTINCIRCLENODE_H
#define A2OOPGAME_SHOOTINCIRCLENODE_H

#include "ShootNode.h"
#include "SoundFx.h"

#include <glm.hpp>

/**
 * Lets an enemy shoot projectiles in a circle.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 08/05/2021]
 */
class ShootInCircleNode : public ShootNode
{
public:
    explicit ShootInCircleNode(BaseEnemy *enemy,
                               const std::string &activateSound="assets/sfx/BeepOne.mp3",
                               const std::string &shotSound="assets/sfx/shurikenThrow.mp3");
    ~ShootInCircleNode() override = default;

    void onAwake() override;
    void onPause() override;

    void action(Ai *ai) override;

protected:
    float mOffSet;
    float mOffSetAdvance;
};


#endif //A2OOPGAME_SHOOTINCIRCLENODE_H
