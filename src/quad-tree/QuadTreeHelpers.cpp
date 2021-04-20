/**
 * @file QuadTreeHelpers.cpp.c
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 16/04/2021
 */
 
#include "QuadTreeHelpers.h"
#include "HelperFunctions.h"
#include <typeinfo>

bool quad::isIntersecting(const rect &rec1, const rect &rec2)
{
    if (rec1.x + rec1.w >= rec2.x && rec1.x <= rec2.x + rec2.w)
    {
        // We have hit on the x-axis.
        if (rec1.y + rec1.h >= rec2.y && rec1.y <= rec2.y + rec2.h)
        {
            return true;  // We have also hit on the y-axis.
        }
    }
    return false;
}

//bool quad::isIntersecting(const quad::Rect &lhs, const quad::Rect &rhs)
//{
//    if (lhs.mPosition.x + lhs.mWidth >= rhs.mPosition.x && lhs.mPosition.x <= rhs.mPosition.x + rhs.mWidth)
//    {
//        // We have hit on the x-axis.
//        if (lhs.mPosition.y + lhs.mHeight >= rhs.mPosition.y && lhs.mPosition.y <= rhs.mPosition.y + rhs.mHeight)
//        {
//            return true;  // We have also hit on the y-axis.
//        }
//    }
//    return false;
//}
//
//bool quad::isIntersecting(const quad::Rect &lhs, const quad::Circle &rhs)
//{
//    glm::vec2 testLocation = rhs.mPosition;
//
//    // Get x pos
//    if (rhs.mPosition.x < lhs.mPosition.x) { testLocation.x = lhs.mPosition.x; }  // Left bound
//    else if (rhs.mPosition.x > lhs.mPosition.x + lhs.mWidth) { testLocation.x = lhs.mPosition.x + lhs.mWidth; }  // Right bound
//
//    // Get y pos
//    if (rhs.mPosition.y < lhs.mPosition.y) { testLocation.y = lhs.mPosition.y; }  // Top bound
//    else if (rhs.mPosition.y > lhs.mPosition.y + lhs.mHeight) { testLocation.y = lhs.mPosition.y + lhs.mHeight; }  // Bottom bound
//
//    glm::vec2 distance = rhs.mPosition - testLocation;
//
//    // True if intersects.
//    return (glm::dot(distance, distance) <= rhs.mRadius * rhs.mRadius);
//}
//
//bool quad::isIntersecting(const quad::Circle &lhs, const quad::Circle &rhs)
//{
//    glm::vec2 distance = lhs.mPosition - rhs.mPosition;
//    float radSquared = lhs.mRadius * lhs.mRadius + rhs.mRadius * rhs.mRadius;
//    return (glm::dot(distance, distance) > radSquared);
//}
//
//bool quad::contains(const quad::Rect &inner, const quad::Rect &outer)
//{
//    return (outer.mPosition.x < inner.mPosition.x &&
//            outer.mPosition.x + outer.mWidth > inner.mPosition.x + inner.mWidth &&
//            outer.mPosition.y < inner.mPosition.y &&
//            outer.mPosition.y + outer.mHeight > inner.mPosition.y + inner.mHeight
//            );
//}
//
//bool quad::contains(const quad::Circle &inner, const quad::Rect &outer)
//{
//    // Test to see if fits.
//    if (outer.mWidth < inner.mRadius) { return false; }
//    // Check to see if the center point lies with the rect.
//    return (inner.mPosition.x < outer.mPosition.x || inner.mPosition.x > outer.mPosition.x + outer.mWidth ||
//            inner.mPosition.y < outer.mPosition.y || inner.mPosition.y > outer.mPosition.y + outer.mHeight);
//}
//
//bool quad::Rect::isIntersecting(const quad::Shape &other)
//{
//    if (typeid(other).hash_code() == typeid(quad::Shape).hash_code())
//    {
//        const auto &otherRect = dynamic_cast<const quad::Rect&>(other);
//        return quad::isIntersecting(*this, otherRect);
//    }
//    else if (typeid(other).hash_code() == typeid(quad::Circle).hash_code())
//    {
//        const auto &otherCircle = dynamic_cast<const quad::Circle&>(other);
//        return quad::isIntersecting(*this, otherCircle);
//    }
//    throwError("Shape was not of type circle or Shape. No intersection tests exists for this type.");
//    return false;
//}
//
//bool quad::Rect::contains(const quad::Shape &other)
//{
//    if (typeid(other).hash_code() == typeid(quad::Circle).hash_code())
//    {
//        const auto &otherCircle = dynamic_cast<const quad::Circle&>(other);
//        return quad::contains(otherCircle, *this);
//    }
//    else if (typeid(other).hash_code() == typeid(quad::Rect).hash_code())
//    {
//        const auto &otherRect = dynamic_cast<const quad::Rect&>(other);
//        return quad::contains(otherRect, *this);
//    }
//    throwError("The shape was not of type circle or shape. No contains test exist for this type.");
//    return false;
//}
//
//bool quad::Circle::isIntersecting(const quad::Shape &other)
//{
//    if (typeid(other).hash_code() == typeid(quad::Circle).hash_code())
//    {
//        const auto &otherCircle = dynamic_cast<const quad::Circle&>(other);
//        return quad::isIntersecting(*this, otherCircle);
//    }
//    else if (typeid(other).hash_code() == typeid(quad::Rect).hash_code())
//    {
//        const auto &otherRect = dynamic_cast<const quad::Rect&>(other);
//        return quad::isIntersecting(otherRect, *this);
//    }
//    throwError("The shape was not of type circle or shape. No intersection tests exits for this type");
//    return false;
//}
//
//bool quad::Circle::contains(const quad::Shape &other)
//{
//    throwError("quad::Circle::contains is not implemented.");
//    return false;
//}
