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

    /**
     * Checks to see if an bounding box fit wholly within a this nodes bounding box.
     * @param aabb The item you want to test against.
     * @return True if it is wholly contained
     */
    bool contains(const quad::rect &aabb);

    /**
     * Attempts to add an item into the tree recursively.
     * @param item The item you are trying to add.
     * @param depth How far down can the item go. 0=this node.
     * @return True if the item was added anywhere in the tree.
     */
    bool insert(quad::data<dataType> &item, int depth=0);

    /**
     * Draw the bounding box of this node.
     * @param renderer What you want to render to.
     */
    void debugRender(Renderer *renderer);

    /**
     * Gets all of the intersecting elements within the tree. NOTE: This will
     * also return the element you query if its within the tree. E.g.: if player
     * was inserted into the tree, and used to find what items will be intersected.
     * Player will be returned.
     * @param aabb The bounding box you want items to intersect.
     * @param queryLayer The layer that is being queried.
     * @param hitItems All items that that have been intersected.
     */
    void getIntersecting(const quad::rect &aabb, const size_t &queryLayer, std::vector<dataType> &hitItems);

protected:
    /**
     * Split a bounding box into 4 sub regions.
     * @param depth If depth is zero. It is unable to subdivide.
     */
    void subdivide(int depth);
    
    const quad::rect mBounds;
    const size_t mSplitThreshold;
    std::array<std::unique_ptr<QuadTreeNode<dataType>>, 4> mSubRegions;
    std::vector<quad::data<dataType>> mItems;
    size_t mLayers;
};


template<class dataType>
QuadTreeNode<dataType>::QuadTreeNode(const quad::rect &rect, const size_t &splitThreshold) :
    mBounds(rect),
    mSplitThreshold(splitThreshold),
    mLayers(0)
{

}

template<class dataType>
bool QuadTreeNode<dataType>::contains(const quad::rect &aabb)
{
    return (mBounds.x < aabb.x && mBounds.x + mBounds.w > aabb.x + aabb.w &&
            mBounds.y < aabb.y && mBounds.y + mBounds.h > aabb.y + aabb.h);
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
            success |= region->insert(item, depth - 1);
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
    mLayers = mLayers | item.layer;  // Add item layer to this node.
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
void QuadTreeNode<dataType>::getIntersecting(const quad::rect &aabb, const size_t &queryLayer,
                                             std::vector<dataType> &hitItems)
{
    if ((queryLayer & mLayers) == 0) { return; }  // Nothing in this node matches the queried layer.
    if (!quad::isIntersecting(mBounds, aabb)) { return; }  // Nothing will be intersecting in this node.

    // Check all items within this node.
    for (quad::data<dataType> &item : mItems)
    {
        if ((queryLayer & item.layer) > 0 && quad::isIntersecting(item.bounds, aabb))
        {
            hitItems.emplace_back(item.value);  // On the correct layer and intersecting.
        }
    }

    // Check items within sub-nodes.
    if (mSubRegions[0])
    {
        for (auto &region : mSubRegions) { region->getIntersecting(aabb, queryLayer, hitItems); }
    }
}


#endif //A2OOPGAME_QUADTREENODE_H
