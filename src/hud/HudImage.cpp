/**
 * @file HudImage.cpp.cc
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include "Player.h"
#include <HudImage.h>

#include "HudElement.h"
#include "LifeGauge.h"
#include "HudImage.h"

#include <utility>

HudImage::HudImage(const glm::ivec2 &position, char anchorPoint, std::string imageRef) :
    HudElement(position, anchorPoint), mImageRef(std::move(imageRef)), mIsRenderable(true)
{
    if (mImageRef.empty()) { mIsRenderable = false; }
}

void HudImage::update()
{

}

std::string HudImage::getImageRef()
{
    return mImageRef;
}

bool HudImage::isRenderable() const
{
    return mIsRenderable;
}