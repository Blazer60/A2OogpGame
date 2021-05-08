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
#include "MomentumProjectile.h"

ShootInCircleNode::ShootInCircleNode(MechaChad *mechaChad) :
        Node(mechaChad, "../tmp/BeepOne.mp3"),
    mFireSound("../sfx/shurikenThrow.mp3"),
    mAmountOfProjectiles(4),
    mOffSet(0)
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
    mOffSet += 47.12f;
    auto points = getUnitCirclePoints(mAmountOfProjectiles, mOffSet);
    for (const auto &point : points)
    {
        mMechaChad->createProjectile(std::make_shared<MomentumProjectile>(mMechaChad->mTransform.position + glm::vec2(128), point * glm::vec2(0.5f), quad::layers::EnemyProjectile));
        mFireSound.play();
    }
}
