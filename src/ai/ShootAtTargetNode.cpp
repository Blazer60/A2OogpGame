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
        Node(mechaChad, "../tmp/BeepOne.mp3"),
    mShootSound("../sfx/shurikenThrow.mp3"),
    mAmountOfProjectiles(3),
    mConeSpread(45.f)
{
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
        mMechaChad->createProjectile(std::make_shared<MomentumProjectile>(mMechaChad->mTransform.position + glm::vec2(128), point * glm::vec2(0.5f), quad::layers::EnemyProjectile));
        mShootSound.play();
    }
}
