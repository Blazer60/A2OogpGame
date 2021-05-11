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
    virtual void onPause();

    /**
     * @param ai The Ai that this node is connect to.
     */
    virtual void update(Ai *ai);

    /**
     * The action that is carried out once the timer is greater than
     * the warm-up time and is an interval of action rate.
     * @param ai The Ai that this node is connect to.
     */
    virtual void action(Ai *ai) = 0;

    void setActionRate(float actionRate);
    void setActionRateMultiplier(float multiplier);
    void setWarmUpTime(int warmUpTime);
    void setMaxTime(int maxTime);
    void setMinimumActionRate(float minimumTime);

protected:
    /** The sound effect played when this node is activated */
    SoundFx mStartSound;

    /** The enemy that this node controls */
    BaseEnemy* mMechaChad;

    /** How long the AI has currently been in this node. (in frames) */
    int mTimer;

    /** How often action() should be called. */
    float mActionRate;

    /**
     * The rate in which action rate should increase/decrease.
     * < 1 = gets faster, > 1 gets slower, = 1 stays the same.
     */
    float mActionRateMultiplier;
    float mMinimumActionRate;

    /** The time before action should be called. */
    int mWarmUpTime;

    /** The maximum time before exiting this node. */
    int mMaxTime;
};


#endif //A2OOPGAME_NODE_H
