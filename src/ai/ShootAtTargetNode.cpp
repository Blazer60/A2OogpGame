/**
 * @file ShootAtTargetNode.cpp.cc
 * @brief A node for the mecha chad to fire towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#include "ShootAtTargetNode.h"
#include "MechaChad.h"
#include "HelperFunctions.h"
#include "MomentumProjectile.h"

ShootAtTargetNode::ShootAtTargetNode(MechaChad *mechaChad) :
        ShootNode(mechaChad, "../tmp/BeepOne.mp3"),
        mConeSpread(45.f)
{
    mAmountOfProjectiles = 3;
    mProjectileSpawnVelocity = glm::vec2 (15.f);
}

void ShootAtTargetNode::onAwake()
{
    Node::onAwake();
}

void ShootAtTargetNode::onPause()
{

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
