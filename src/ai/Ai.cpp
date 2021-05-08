/**
 * @file Ai.cpp.cc
 * @brief An Ai manager that changes between different states. Currently tied to mecha chad.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "Ai.h"
#include "ChargeNode.h"
#include "ShootInCircleNode.h"
#include "ShootAtTargetNode.h"
#include "MechaChad.h"


Ai::Ai(MechaChad *mMechaChad) : mMechaChad(mMechaChad), mCurrNodeId(selector::Charge)
{
    mNodes[0] = (std::make_unique<ChargeNode>(mMechaChad));
    mNodes[1] = (std::make_unique<ShootAtTargetNode>(mMechaChad));
    mNodes[2] = (std::make_unique<ShootInCircleNode>(mMechaChad));
}

void Ai::update()
{
    mNodes[mCurrNodeId]->update(this);
}

void Ai::switchCurrentNode(int nodeRef)
{
    mMechaChad->mVelocity = glm::vec2(0.f);
    mNodes[mCurrNodeId]->onPause();
    mCurrNodeId = nodeRef;
    mNodes[mCurrNodeId]->onAwake();
}
