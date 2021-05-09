/**
 * @file Node.h
 * @brief An AI Node that can do basic behaviour.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_NODE_H
#define A2OOPGAME_NODE_H

#include "SoundFx.h"

class BaseEnemy;
class Ai;

/**
 * An AI Node that can do basic behaviour.
 * @see MechaChad
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class Node
{
public:
    Node(BaseEnemy *enemy, const std::string &soundPath);
    virtual ~Node() = default;

    virtual void onAwake();
    virtual void onPause() = 0;

    virtual void update(Ai *ai);

    /**
     * The action that is carried out once the timer meets certain criteria.
     * @param ai
     */
    virtual void action(Ai *ai) = 0;

protected:
    SoundFx mStartSound;

    BaseEnemy* mMechaChad;
    int mTimer;         // The general timer
    int mActionRate;    // How often action should be called.
    int mWarmUpTime;    // The time before action should be called.
    int mMaxTime;       // The maximum time before leaving this node.
};


#endif //A2OOPGAME_NODE_H
