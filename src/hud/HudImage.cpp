/**
 * @file HudImage.cpp.cc
 * @brief An image that can be renderer to the screen
 * regardless of where the 'camera' position is.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include "HudImage.h"

HudImage::HudImage(const glm::ivec2 &position, char anchorPoint, std::string imageRef) :
    HudElement(position, anchorPoint), mImageRef(std::move(imageRef))
{
    if (mImageRef.empty()) { mIsRenderable = false; }
}

void HudImage::update()
{}

std::string HudImage::getImageRef()
{
    return mImageRef;
}

