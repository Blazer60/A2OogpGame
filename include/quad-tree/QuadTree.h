/**
 * @file QuadTree.h
 * @brief A Quad Tree that can hold information about entities. Interfaces with quad tree nodes.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 16/04/2021
 */


#ifndef A2OOPGAME_QUADTREE_H
#define A2OOPGAME_QUADTREE_H

#include "QuadTreeHelpers.h"
#include "QuadTreeNode.h"

#include <vector>
#include <memory>
#include <glm.hpp>


/**
 * A Quad Tree that can hold information about entities. Interfaces with quad tree nodes.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 16/04/2021]
 */
template<class dataType>
class QuadTree
{
public:
    explicit QuadTree(const quad::rect &bounds, const size_t &maxDepth=10);

    void insert(const dataType &data, const quad::rect &rect);

protected:
    const std::unique_ptr<QuadTreeNode<dataType>> mRootNode;
    const quad::rect mBounds;
    const size_t mMaxDepth;
    std::vector<quad::data<dataType>> mUnboundItems;
};

template<class dataType>
QuadTree<dataType>::QuadTree(const quad::rect &bounds, const size_t &maxDepth) :
    mBounds(bounds),
    mMaxDepth(maxDepth),
    mRootNode(std::make_unique<QuadTreeNode<dataType>>(bounds))
{
}

template<class dataType>
void QuadTree<dataType>::insert(const dataType &data, const quad::rect &rect)
{
    quad::data<dataType> item{ rect, data };
    bool success = mRootNode->insert(item);
    if (!success) { mUnboundItems.emplace_back(item); }
}


#endif //A2OOPGAME_QUADTREE_H
