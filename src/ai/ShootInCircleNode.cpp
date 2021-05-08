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
        Node(mechaChad, "../tmp/BeepOne.mp3"),
    mFireSound("../sfx/shurikenThrow.mp3"),
    mAmountOfProjectiles(4),
    mOffSet(0),
    mProjectileType(projectiles::Default),
    mOffSetAdvance(47.12f),
    mProjectileSpawnVelocity(15.f)
{}

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
        mFireSound.play();
    }
}

void ShootInCircleNode::setProjectileType(char type)
{
    mProjectileType = type;
}
