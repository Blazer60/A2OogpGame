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

ChargeNode::ChargeNode(BaseEnemy *enemy, const std::string &activateSound) :
    Node(enemy, activateSound), mSpeed(10.f), mMaxSpeed(20.f), mSpeedMultiplier(1.02f)
{
    mMinimumActionRate = 1;
    mActionRate = 1;  // Happens every frame.
    mMaxTime = 60;
}

void ChargeNode::onAwake()
{
    Node::onAwake();
}

void ChargeNode::onPause()
{
    Node::onPause();
    mSpeed *= mSpeedMultiplier;
    if (mSpeed > mMaxSpeed) { mSpeed = mMaxSpeed; }
}

void ChargeNode::action(Ai *ai)
{
    auto targetDirection = mMechaChad->getTargetDirection();
    mMechaChad->mVelocity = targetDirection * mSpeed;
    mMechaChad->mTransform.position += mMechaChad->mVelocity;
}
