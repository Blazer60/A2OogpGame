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

class Renderer;

/**
 * A Quad Tree that can hold information about entities. Interfaces with quad tree nodes.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 16/04/2021]
 */
template<class dataType>
class QuadTree
{
public:
    explicit QuadTree(const quad::rect &bounds, const size_t &splitThreshold=10, const size_t &maxDepth=10);

    void insert(const dataType &data, const quad::rect &rect);
    void debugRender(Renderer *renderer);
    // This will return itself. E.g.: player passed in will return player.
    std::vector<dataType> getIntersecting(const quad::rect &element);

protected:
    const std::unique_ptr<QuadTreeNode<dataType>> mRootNode;
    const quad::rect mBounds;
    const size_t mMaxDepth;
    const size_t mSplitThreshold;
    std::vector<quad::data<dataType>> mUnboundItems;
};

template<class dataType>
QuadTree<dataType>::QuadTree(const quad::rect &bounds, const size_t &splitThreshold, const size_t &maxDepth) :
    mBounds(bounds),
    mMaxDepth(maxDepth),
    mRootNode(std::make_unique<QuadTreeNode<dataType>>(bounds, splitThreshold)),
    mSplitThreshold(splitThreshold)
{
}

template<class dataType>
void QuadTree<dataType>::insert(const dataType &data, const quad::rect &rect)
{
    quad::data<dataType> item{ rect, data };
    bool success = mRootNode->insert(item, mMaxDepth);
    if (!success) { mUnboundItems.emplace_back(item); }
}

template<class dataType>
void QuadTree<dataType>::debugRender(Renderer *renderer)
{
    mRootNode->debugRender(renderer);
}

template<class dataType>
std::vector<dataType> QuadTree<dataType>::getIntersecting(const quad::rect &element)
{
    std::vector<dataType> hitItems;
    for (quad::data<dataType> &item : mUnboundItems)
    {
        if (quad::isIntersecting(item.bounds, element)) { hitItems.emplace_back(item.value); }
    }
    mRootNode->getIntersecting(element, hitItems);
    return hitItems;
}


#endif //A2OOPGAME_QUADTREE_H
