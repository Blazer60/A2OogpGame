/**
 * @file Node.cpp.cc
 * @brief An AI Node that can do basic behaviour.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "Node.h"
#include "Ai.h"

Node::Node(BaseEnemy *enemy, const std::string &soundPath) :
    mMechaChad(enemy),
    mStartSound(soundPath),
    mActionRate(30.f),
    mMaxTime(150),
    mTimer(0),
    mWarmUpTime(15),
    mActionRateMultiplier(1.f),
    mMinimumActionRate(5.f)
{}

void Node::onAwake()
{
    mTimer = 0;
    mStartSound.play();
}

void Node::onPause()
{
    mActionRate *= mActionRateMultiplier;
    if (mActionRate < mMinimumActionRate) { mActionRate = mMinimumActionRate; }
}

void Node::update(Ai *ai)
{
    mTimer++;
    if (mTimer > mWarmUpTime)
    {
        // Only perform the action every so often rather than every frame.
        if (mTimer % static_cast<int>(mActionRate) == 0)
        {
            action(ai);
        }
    }
    if (mTimer > mMaxTime)
    {
        ai->switchCurrentNode();
    }
}

void Node::setActionRate(float actionRate)
{
    mActionRate = actionRate;
}

void Node::setWarmUpTime(int warmUpTime)
{
    mWarmUpTime = warmUpTime;
}

void Node::setMaxTime(int maxTime)
{
    mMaxTime = maxTime;
}

void Node::setMinimumActionRate(float minimumTime)
{
    mMinimumActionRate = minimumTime;
}

void Node::setActionRateMultiplier(float multiplier)
{
    mActionRateMultiplier = multiplier;
}
