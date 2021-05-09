/**
 * @file ChargeNode.cpp.cc
 * @brief A node that makes an enemy charge towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#include "ChargeNode.h"
#include "BaseEnemy.h"

ChargeNode::ChargeNode(BaseEnemy *enemy) : Node(enemy, "../tmp/BeepOne.mp3"),
                                           mSpeed(10.f), mMaxSpeed(20.f), mSpeedMultiplier(1.02f)
{
    mActionRate = 1;  // Happens continuously until mecha chad stops.
    mMaxTime = 60;
}

void ChargeNode::onAwake()
{
    Node::onAwake();
    mSpeed *= mSpeedMultiplier;
    if (mSpeed > mMaxSpeed) { mSpeed = mMaxSpeed; }
}

void ChargeNode::onPause()
{

}

void ChargeNode::action(Ai *ai)
{
    auto targetDirection = mMechaChad->getTargetDirection();
    mMechaChad->mVelocity = targetDirection * mSpeed;
    mMechaChad->mTransform.position += mMechaChad->mVelocity;
//    mMechaChad->chargeTarget(mSpeed);
}
