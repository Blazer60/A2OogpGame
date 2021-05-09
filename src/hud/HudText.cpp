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
#include "HudElement.h"


HudText::HudText(const glm::ivec2 &position, char anchorPoint) :
    HudElement(position, anchorPoint), mSize(32), mFontPath("assets/ttf/unispace-bd.ttf"),
    mText("PlaceHolderText"), mId(0), mColour({ 215, 215, 215, 255 }), mTextData(nullptr),
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

void HudText::setSize(int newSize)
{
    freeTextData();
    mSize = newSize;
    createTextData();
    mIsRendererValid = false;
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

void HudText::update()
{

}

void HudText::setPosition(const glm::ivec2 &newPosition)
{
    mTransform.position = newPosition;
}

bool HudText::isVisible() const
{
    return mIsRenderable;
}

void HudText::setVisibility(bool visibility)
{
    mIsRenderable = visibility;
}

SDL_Color HudText::getColour() const
{
    return mColour;
}

void HudText::setColour(const SDL_Color &colour)
{
    mColour = colour;
    mIsRendererValid = false;
}


