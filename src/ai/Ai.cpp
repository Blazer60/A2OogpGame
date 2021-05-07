/**
 * @file Ai.cpp.cc
 * @brief An Ai manager that changes between different states. Currently tied to mecha chad.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#include "Ai.h"
#include "Node.h"



Ai::Ai(MechaChad *mMechaChad) : mMechaChad(mMechaChad), mCurrNodeId(selector::Charge)
{

}

void Ai::update()
{
    mNodes[mCurrNodeId].update(this);
}

void Ai::switchCurrentNode(int nodeRef)
{
    mNodes[mCurrNodeId].onPause();
    mCurrNodeId = nodeRef;
    mNodes[mCurrNodeId].onAwake();
}
