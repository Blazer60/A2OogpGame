/**
 * @file QuadTreeNode.h
 * @brief An internal or leaf node within a quad tree.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 16/04/2021
 */


#ifndef A2OOPGAME_QUADTREENODE_H
#define A2OOPGAME_QUADTREENODE_H

#include "QuadTreeHelpers.h"

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include "Renderer.h"

/**
 * An internal or leaf node within a quad tree.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 16/04/2021]
 */
template<class dataType>
class QuadTreeNode
{
public:
    explicit QuadTreeNode(const quad::rect &rect, const size_t &splitThreshold=10);

    bool contains(const quad::rect &other);
    bool insert(quad::data<dataType> &item, int depth=0);
    void debugRender(Renderer *renderer);

protected:
    void subdivide(int depth);
    
    const quad::rect mBounds;
    const size_t mSplitThreshold;
    std::array<std::unique_ptr<QuadTreeNode<dataType>>, 4> mSubRegions;
    std::vector<quad::data<dataType>> mItems;
};


template<class dataType>
QuadTreeNode<dataType>::QuadTreeNode(const quad::rect &rect, const size_t &splitThreshold) :
    mBounds(rect),
    mSplitThreshold(splitThreshold)
{

}

template<class dataType>
bool QuadTreeNode<dataType>::contains(const quad::rect &other)
{
    return (mBounds.x < other.x && mBounds.x + mBounds.w > other.x + other.w &&
        mBounds.y < other.y && mBounds.y + mBounds.h > other.y + other.h);
}

template<class dataType>
bool QuadTreeNode<dataType>::insert(quad::data<dataType> &item, int depth)
{
    if (!contains(item.bounds)) { return false; }  // We cannot insert the data into this node.
    if (mSubRegions[0])
    {
        // We have child nodes that could potentially insert the data.
        bool success = false;
        for (auto &region : mSubRegions)
        {
            success |= region->insert(item, depth-1);
        }
        if (!success)
        {
            // Add the item in this node.
            mItems.emplace_back(item);
        }
    }
    else
    {
        mItems.emplace_back(item);
        subdivide(depth);  // Will try and subdivide if the number of elements exceeds the specified threshold.
    }
    return true;
}

template<class dataType>
void QuadTreeNode<dataType>::subdivide(int depth)
{
    if (depth <= 0) { return; }  // We can't go any further down.
    if (mItems.size() < mSplitThreshold) { return; }  // Don't subdivide.
    
    // Create the four regions.
    float halfHeight = mBounds.w / 2, halfWidth = mBounds.h / 2;
    
    quad::rect northWestRegion = { mBounds.x,                   mBounds.y,                    halfWidth, halfHeight };
    quad::rect northEastRegion = { mBounds.x + halfWidth,   mBounds.y,                    halfWidth, halfHeight };
    quad::rect southEastRegion = { mBounds.x + halfWidth,   mBounds.y + halfHeight,   halfWidth, halfHeight };
    quad::rect southWestRegion = { mBounds.x,                   mBounds.y + halfHeight,   halfWidth, halfHeight };
    
    mSubRegions[quad::NorthWest] = std::make_unique<QuadTreeNode<dataType>>(northWestRegion);
    mSubRegions[quad::NorthEast] = std::make_unique<QuadTreeNode<dataType>>(northEastRegion);
    mSubRegions[quad::SouthEast] = std::make_unique<QuadTreeNode<dataType>>(southEastRegion);
    mSubRegions[quad::SouthWest] = std::make_unique<QuadTreeNode<dataType>>(southWestRegion);

    std::vector<quad::data<dataType>> tmp = mItems;
    mItems.clear();
    for (auto &item : tmp) { insert(item); }  // All items should be able to be re-inserted.
}

template<class dataType>
void QuadTreeNode<dataType>::debugRender(Renderer *renderer)
{
    renderer->renderHitBox(glm::vec4{ mBounds.x, mBounds.y, mBounds.w, mBounds.h });
    if (mSubRegions[0])
    {
        for (auto &region : mSubRegions) { region->debugRender(renderer); }
    }
}


#endif //A2OOPGAME_QUADTREENODE_H
