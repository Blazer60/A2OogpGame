/**
 * @file Node.h
 * @brief An AI Node that can do basic behaviour. Purposely built with Mecha Chad in mind.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_NODE_H
#define A2OOPGAME_NODE_H

class MechaChad;
class Ai;

/**
 * An AI Node that can do basic behaviour. Purposely built with Mecha Chad in mind.
 * @see MechaChad
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class Node
{
public:
    explicit Node(MechaChad *mechaChad);

    virtual void onAwake() = 0;
    virtual void onPause() = 0;

    virtual void update(Ai *ai) = 0;

protected:
    MechaChad* mechaChad;
};


#endif //A2OOPGAME_NODE_H
