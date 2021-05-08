/**
 * @file ChargeNode.cpp.cc
 * @brief A node that makes mecha chad charge towards its target.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 08/05/2021
 */


#include "ChargeNode.h"
#include "MechaChad.h"

ChargeNode::ChargeNode(MechaChad *mechaChad) : Node(mechaChad, 0, "../tmp/BeepOne.mp3")
{
    mActionRate = 1;  // Happens continuously until he stops.
    mMaxTime = 60;
}

void ChargeNode::onAwake()
{
    Node::onAwake();
    mStartSound.play();
}

void ChargeNode::onPause()
{

}

void ChargeNode::action(Ai *ai)
{
    mMechaChad->chargeTarget();
}
