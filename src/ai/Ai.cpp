/**
 * @file Ai.cpp.cc
 * @brief An Ai manager that changes between different states. Currently tied to mecha chad.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "Ai.h"

#include <utility>
#include "MechaChad.h"
#include "HelperFunctions.h"


Ai::Ai(MechaChad *mMechaChad) : mMechaChad(mMechaChad), mCurrConnectionId(0)
{
}

void Ai::setConnections(std::vector<int> newConnections)
{
    mConnections = std::move(newConnections);
    mCurrConnectionId = 0;
    mCurrNode = mNodes.begin();
}

void Ai::createNode(int key, std::unique_ptr<Node> lock)
{
    mNodes[key] = std::move(lock);
}

void Ai::update()
{
    mCurrNode->second->update(this);
}

void Ai::switchCurrentNode()
{
    mMechaChad->mVelocity = glm::vec2(0.f);
    mCurrNode->second->onPause();

    mCurrConnectionId = (mCurrConnectionId + 1) % static_cast<int>(mConnections.size());
    mCurrNode = mNodes.find(mConnections[mCurrConnectionId]);
    if (mCurrNode == mNodes.end()) { throwError("No node exists within this topology."); }

    mCurrNode->second->onAwake();
}
