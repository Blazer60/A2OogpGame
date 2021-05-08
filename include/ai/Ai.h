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

#include "Node.h"

#include <vector>
#include <unordered_map>
#include <memory>

class MechaChad;

/**
 * An Ai manager that changes between different states. Currently tied to mecha chad.
 * @see MechaChad.h
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class Ai
{
    typedef std::unordered_map<int, std::unique_ptr<Node>> nodeMap;
public:
    explicit Ai(MechaChad *mMechaChad);
    ~Ai() = default;

    void update();
    void switchCurrentNode();
    void createNode(int key, std::unique_ptr<Node> lock);
    void setConnections(std::vector<int> newConnections);

protected:
    MechaChad* mMechaChad;
    nodeMap mNodes;
    int mCurrConnectionId;
    std::vector<int> mConnections;
    nodeMap::iterator mCurrNode;
};


#endif //A2OOPGAME_AI_H
