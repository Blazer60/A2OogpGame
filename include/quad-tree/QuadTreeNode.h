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
    bool insert(const quad::data<dataType> &item, int depth=0);

protected:
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
bool QuadTreeNode<dataType>::insert(const quad::data<dataType> &item, int depth)
{
    if (!contains(item.bounds)) { return false; }  // We cannot insert the data into this node.
    if (mSubRegions[0])
    {
        // We have child nodes that could potentially insert the data.
        bool success = false;
        for (auto &region : mSubRegions)
        {
            success |= region->insert(item, depth+1);
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
    }
    return true;
}


#endif //A2OOPGAME_QUADTREENODE_H
