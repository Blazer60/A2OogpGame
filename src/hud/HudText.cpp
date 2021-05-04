/**
 * @file HudText.cpp.cc
 * @brief Text that can appear on the HUD.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include "HudText.h"



HudText::HudText(const glm::ivec2 &position, char anchorPoint) :
    HudElement(position, anchorPoint), mSize(32), mFontPath("../tmp/unispace-bd.ttf"),
    mText("PlaceHolderText"), mId(nullptr), mColour(glm::vec4(255.f))
{

}

void HudText::setText(const std::string &text)
{
    HudText::mText = text;
}
