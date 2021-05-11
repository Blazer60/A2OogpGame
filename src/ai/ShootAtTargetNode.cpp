/**
 * @file ShootAtTargetNode.cpp.cc
 * @brief A node for the enemy to fire towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#include "ShootAtTargetNode.h"
#include "HelperFunctions.h"
#include "BaseEnemy.h"

ShootAtTargetNode::ShootAtTargetNode(BaseEnemy *enemy, const std::string &activateSound, const std::string &shotSound) :
        ShootNode(enemy, activateSound, shotSound),
        mConeSpread(20.f), mConeSpreadMultiplier(1.1f)
{
    mAmountOfProjectiles = 3;
    mProjectileSpawnVelocity = glm::vec2 (15.f);
    mActionRateMultiplier = 0.95f;
}

void ShootAtTargetNode::onAwake()
{
    Node::onAwake();
}

void ShootAtTargetNode::onPause()
{
    Node::onPause();
    mAmountOfProjectiles += mProjectileCountIncrease;
    mConeSpread *= mConeSpreadMultiplier;
}

void ShootAtTargetNode::action(Ai *ai)
{
    auto targetDirection = mMechaChad->getTargetDirection();
    auto points = getUnitConePoints(mAmountOfProjectiles, targetDirection, mConeSpread);
    for (const auto &point : points)
    {
        mMechaChad->createProjectile(point * mProjectileSpawnVelocity, mProjectileType);
        mShootSound.play();
    }
}

void ShootAtTargetNode::setConeSpread(float coneSpread)
{
    mConeSpread = coneSpread;
}

void ShootAtTargetNode::setConeSpreadMultiplier(float multiplier)
{
    mConeSpreadMultiplier = multiplier;
}
