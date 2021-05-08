/**
 * @file Node.cpp.cc
 * @brief An AI Node that can do basic behaviour. Purposely built with Mecha Chad in mind.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "Node.h"
#include "Ai.h"

Node::Node(MechaChad *mechaChad, int nextNodeId, const std::string &soundPath) :
    mMechaChad(mechaChad),
    mStartSound(soundPath),
    mNextNodeId(nextNodeId),
    mActionRate(30),
    mMaxTime(150),
    mTimer(0),
    mWarmUpTime(15)
{}

void Node::onAwake()
{
    mTimer = 0;
    mStartSound.play();
}

void Node::update(Ai *ai)
{
    mTimer++;
    if (mTimer > mWarmUpTime)
    {
        if (mTimer % mActionRate == 0)
        {
            action(ai);
        }
    }
    if (mTimer > mMaxTime)
    {
        ai->switchCurrentNode(mNextNodeId);
    }
}
