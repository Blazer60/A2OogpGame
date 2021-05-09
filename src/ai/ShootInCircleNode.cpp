/**
 * @file ShootInCircleNode.cpp.cc
 * @brief Lets mecha chad shoot projectiles in a circle.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#include "ShootInCircleNode.h"
#include "MechaChad.h"
#include "HelperFunctions.h"

ShootInCircleNode::ShootInCircleNode(MechaChad *mechaChad) :
        ShootNode(mechaChad, "../tmp/BeepOne.mp3"),
        mOffSet(0),
        mOffSetAdvance(47.12f)
{
    mAmountOfProjectiles = 4;
    mProjectileSpawnVelocity = glm::vec2(15.f);
}

void ShootInCircleNode::onAwake()
{
    Node::onAwake();
}

void ShootInCircleNode::onPause()
{

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

void ShootInCircleNode::setProjectileType(char type)
{
    mProjectileType = type;
}
