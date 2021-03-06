/**
 * @file StateMachine.cpp.cc
 * @brief The base class used for State Machines.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "StateMachine.h"
#include "StateMachineManager.h"

StateMachine::StateMachine(SDL_Renderer *renderer, const glm::ivec2 &windowSize, char stateKey) :
        mRenderer(renderer, windowSize), mStateKey(stateKey)
{}

void StateMachine::changeState(StateMachineManager *smm, char stateKey)
{
    smm->changeState(stateKey);
}

char StateMachine::getStateKey() const
{
    return mStateKey;
}

void StateMachine::flip()
{
    mRenderer.flip();
}

