/**
 * @file Ai.h
 * @brief An Ai manager that changes between different states.
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

class BaseEnemy;

/**
 * An Ai manager that changes between different states.
 * @see MechaChad.h
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 07/05/2021]
 */
class Ai
{
    typedef std::unordered_map<int, std::unique_ptr<Node>> nodeMap;
public:
    explicit Ai(BaseEnemy *enemy);
    ~Ai() = default;

    void update();

    /**
     * Continuously iterates over nodes until the stage is reached.
     * Used for debugging purposes.
     * @param stage How far in/difficult you want the AI to be.
     */
    void advanceToStage(int stage);

    /**
     * Creates a new node that can be used in connections
     * @param key Used to access the data later on.
     * @param lock The node you want to store in the AI.
     */
    void createNode(int key, std::unique_ptr<Node> lock);

    /**
     * Sets the connection paths that the AI will follow.
     * E.g.: Move, Shoot, Move. Where move is a single node in
     * the AI.
     * @param newConnections The list that the AI will follow.
     */
    void setConnections(std::vector<int> newConnections);

    /**
     * Switches to the next node in the chain. Loops back to the
     * start if there are no more elements in mConnections.
     */
    void switchCurrentNode();

protected:
    BaseEnemy* mEnemy;
    nodeMap mNodes;
    nodeMap::iterator mCurrNode;

    int mCurrConnectionId;
    std::vector<int> mConnections;
};


#endif //A2OOPGAME_AI_H
