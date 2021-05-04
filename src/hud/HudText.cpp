/**
 * @file HudText.cpp.cc
 * @brief Text that can appear on the HUD.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include "HudText.h"
#include "HelperFunctions.h"


HudText::HudText(const glm::ivec2 &position, char anchorPoint) :
    HudElement(position, anchorPoint), mSize(32), mFontPath("../tmp/unispace-bd.ttf"),
    mText("PlaceHolderText"), mId(0), mColour(glm::vec4(255.f)), mTextData(nullptr),
    mIsRendererValid(false)
{
    createTextData();
}

HudText::~HudText()
{
    freeTextData();
}

void HudText::createTextData()
{
    mTextData = TTF_OpenFont(mFontPath.c_str(), mSize);
    if (!mTextData) { throwWarning("Could not load the font. Check the file path."); }
}

void HudText::freeTextData()
{
    TTF_CloseFont(mTextData);
    mTextData = nullptr;
}

void HudText::setText(const std::string &text)
{
    HudText::mText = text;
    mIsRendererValid = false;
}

std::string HudText::getText() const
{
    return mText;
}

void HudText::setId(size_t newId)
{
    mId = newId;
}

size_t HudText::getId() const
{
    return mId;
}

int HudText::getSize() const
{
    return mSize;
}

TTF_Font *HudText::getTextData() const
{
    return mTextData;
}

bool HudText::isRenderValid() const
{
    return mIsRendererValid;
}

void HudText::setRenderValid(bool isValid)
{
    mIsRendererValid = isValid;
}

glm::ivec2 HudText::getPosition() const
{
    return mTransform.position;
}

void HudText::update()
{

}
