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
#include "Renderer.h"

#include <array>
#include <vector>
#include <memory>
#include <iostream>


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
    // This will intersect itself. E.g.: Player passed in will return player out.
    void getIntersecting(const quad::rect &element, std::vector<dataType> &hitItems);

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
    float halfHeight = mBounds.h / 2, halfWidth = mBounds.w / 2;
    
    quad::rect northWestRegion = { mBounds.x,                   mBounds.y,                    halfWidth, halfHeight };
    quad::rect northEastRegion = { mBounds.x + halfWidth,   mBounds.y,                    halfWidth, halfHeight };
    quad::rect southEastRegion = { mBounds.x + halfWidth,   mBounds.y + halfHeight,   halfWidth, halfHeight };
    quad::rect southWestRegion = { mBounds.x,                   mBounds.y + halfHeight,   halfWidth, halfHeight };
    
    mSubRegions[quad::NorthWest] = std::make_unique<QuadTreeNode<dataType>>(northWestRegion, mSplitThreshold);
    mSubRegions[quad::NorthEast] = std::make_unique<QuadTreeNode<dataType>>(northEastRegion, mSplitThreshold);
    mSubRegions[quad::SouthEast] = std::make_unique<QuadTreeNode<dataType>>(southEastRegion, mSplitThreshold);
    mSubRegions[quad::SouthWest] = std::make_unique<QuadTreeNode<dataType>>(southWestRegion, mSplitThreshold);

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
        mSubRegions[quad::NorthWest]->debugRender(renderer);
        mSubRegions[quad::NorthEast]->debugRender(renderer);
        mSubRegions[quad::SouthEast]->debugRender(renderer);
        mSubRegions[quad::SouthWest]->debugRender(renderer);
    }
}

template<class dataType>
void QuadTreeNode<dataType>::getIntersecting(const quad::rect &element, std::vector<dataType> &hitItems)
{
    if (!quad::isIntersecting(mBounds, element)) { return; }  // Nothing will be intersecting in this node.

    // Check all items within this node.
    for (quad::data<dataType> &item : mItems)
    {
        if (quad::isIntersecting(item.bounds, element)) { hitItems.emplace_back(item.value); }
    }

    // Check items within sub-nodes.
    if (mSubRegions[0])
    {
        for (auto &region : mSubRegions) { region->getIntersecting(element, hitItems); }
    }
}


#endif //A2OOPGAME_QUADTREENODE_H
