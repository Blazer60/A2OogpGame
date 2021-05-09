/**
 * @file ShootInCircleNode.cpp.cc
 * @brief Lets an enemy shoot projectiles in a circle.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#include "ShootInCircleNode.h"
#include "BaseEnemy.h"
#include "HelperFunctions.h"
#include "ShootNode.h"

ShootInCircleNode::ShootInCircleNode(BaseEnemy *enemy) :
        ShootNode(enemy, "../tmp/BeepOne.mp3"),
        mOffSet(0),
        mOffSetAdvance(47.12f)
{
    mAmountOfProjectiles = 8;
    mProjectileSpawnVelocity = glm::vec2(15.f);
    mActionRateMultiplier = 0.9f;
}

void ShootInCircleNode::onAwake()
{
    Node::onAwake();
}

void ShootInCircleNode::onPause()
{
    Node::onPause();
    mAmountOfProjectiles += mProjectileCountIncrease;
    mOffSet = 0;
}

void ShootInCircleNode::action(Ai *ai)
{
    mOffSet += mOffSetAdvance;
    auto points = getUnitCirclePoints(mAmountOfProjectiles, mOffSet);
    for (const auto &point : points)
    {
        mMechaChad->createProjectile(point * mProjectileSpawnVelocity, mProjectileType);
        mShootSound.play();
    }
}

