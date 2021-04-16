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

    /**
     * Inserts an item into the tree.
     * @param data The item data you want to store.
     * @param aabb The bounding box to find said data.
     */
    void insert(const dataType &data, const quad::rect &aabb);

    /**
     * Renders the bounding boxes of the quad tree. Only to be used in debug mode.
     * @param renderer What you want to render to.
     */
    void debugRender(Renderer *renderer);

    /**
     * Gets all of the intersecting elements within the tree. NOTE: This will
     * also return the element you query if its within the tree. E.g.: if player
     * was inserted into the tree, and used to find what items will be intersected.
     * Player will be returned.
     * @param aabb The bounding box you want items to intersect.
     * @return All elements intersecting your query.
     */
    std::vector<dataType> getIntersecting(const quad::rect &aabb);

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
void QuadTree<dataType>::insert(const dataType &data, const quad::rect &aabb)
{
    quad::data<dataType> item{ aabb, data };
    bool success = mRootNode->insert(item, mMaxDepth);
    if (!success) { mUnboundItems.emplace_back(item); }
}

template<class dataType>
void QuadTree<dataType>::debugRender(Renderer *renderer)
{
    mRootNode->debugRender(renderer);
}

template<class dataType>
std::vector<dataType> QuadTree<dataType>::getIntersecting(const quad::rect &aabb)
{
    std::vector<dataType> hitItems;
    for (quad::data<dataType> &item : mUnboundItems)
    {
        if (quad::isIntersecting(item.bounds, aabb)) { hitItems.emplace_back(item.value); }
    }
    mRootNode->getIntersecting(aabb, hitItems);
    return hitItems;
}


#endif //A2OOPGAME_QUADTREE_H
