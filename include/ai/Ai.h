/**
 * @file Ai.h
 * @brief An Ai manager that changes between different states. Currently tied to mecha chad.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 07/05/2021
 */


#ifndef A2OOPGAME_AI_H
#define A2OOPGAME_AI_H

#include <vector>

class MechaChad;
class Node;

/**
 * An Ai manager that changes between different states. Currently tied to mecha chad.
 * @see MechaChad.h
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class Ai
{
    enum selector : int { Charge, ShootAtTarget, ShootInCircle };
public:
    explicit Ai(MechaChad *mMechaChad);
    ~Ai() = default;

    void update();
    void switchCurrentNode(int nodeRef);

protected:
    MechaChad* mMechaChad;
    std::vector<Node> mNodes;
    int mCurrNodeId;
};


#endif //A2OOPGAME_AI_H
