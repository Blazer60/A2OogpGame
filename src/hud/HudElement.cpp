/**
 * @file HudElement.cpp.cc
 * @brief Abstract base class for elements that are
 * not impacted by the position of the camera.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include <utility>
#include <HudImage.h>
#include "Player.h"
#include "HelperFunctions.h"
#include "HudText.h"
#include "LifeGauge.h"
#include "HudElement.h"

hudTransform::hudTransform(const glm::ivec2 &position, double rotation, const glm::vec2 &scale) : position(position),
                                                                                                  rotation(rotation),
                                                                                                  scale(scale)
{}

HudElement::HudElement(const glm::ivec2 &position, char anchorPoint) :
        mTransform(position, 0, glm::vec2(1)),
        mAnchorPoint(anchorPoint), mIsRenderable(true)
{

}

char HudElement::getAnchorPoint() const
{
    return mAnchorPoint;
}

void HudElement::setAnchorPoint(char anchorPoint)
{
    HudElement::mAnchorPoint = anchorPoint;
}

glm::ivec2 HudElement::getPosition() const
{
    return mTransform.position;
}

glm::vec2 HudElement::getScale() const
{
    return mTransform.scale;
}

bool HudElement::isRenderable() const
{
    return mIsRenderable;
}