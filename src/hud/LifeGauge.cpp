/**
 * @file LifeGauge.cpp.cc
 * @brief The life gauge that shows how many lives that player has.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include "LifeGauge.h"
#include "HudImage.h"
#include "HudElement.h"

LifeGauge::LifeGauge(const glm::ivec2 &position, char anchorPoint) :
    HudImage(position, anchorPoint, "assets/images/ThreeHearts-0001.png"),
    mCurrentRefNumber(3),
    mLifeImages({ "",
                  "assets/images/OneHeart-0001.png",
                  "assets/images/TwoHearts-0001.png",
                  "assets/images/ThreeHearts-0001.png" })
{
    mTransform.scale = glm::vec2(2.f);
}

void LifeGauge::setImageRef(int refNumber)
{
    if (!(0 <= refNumber && refNumber <= 3)) { refNumber = 0; }
    mImageRef = mLifeImages[refNumber];
    mCurrentRefNumber = refNumber;

    mIsRenderable = !mImageRef.empty();
}

int LifeGauge::getCurrentRefNumber() const
{
    return mCurrentRefNumber;
}

