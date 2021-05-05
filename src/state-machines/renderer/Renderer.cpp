/**
 * @file Renderer.cpp.cc
 * @brief Handles rendering entities to the screen. Each state machine contains their own renderer.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "Renderer.h"
#include "HelperFunctions.h"
#include "Entity.h"
#include "HudText.h"
#include "HudImage.h"
#include "HudElement.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <QuadTreeHelpers.h>

Renderer::Renderer(SDL_Window *window) :
        mRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
        mInterpolation(0.f), mPosition(0), mRendererSize(windowSizeToVec2(window)),
        mNextTextId(1)
{}

Renderer::~Renderer()
{
    for (auto &item : mImages)
    {
        SDL_DestroyTexture(item.second.src);
    }
    // We can't erase in place while iterating.
    mImages.clear();

    // Do the same for all of the HUD elements
    for (auto &item : mTexts)
    {
        SDL_DestroyTexture(item.second.src);
    }

    mTexts.clear();
}

void Renderer::flip()
{
    SDL_RenderPresent(mRenderer);
}

void Renderer::renderItem(const std::shared_ptr<Entity> &entity)
{
    if (!entity->mIsRenderable) { return; }  // The entity has been marked as non-renderable.
    auto imageIt = mImages.find(entity->mImageRef);
    if (imageIt == mImages.end()) { throwError("Could not find entities image src."); }

    glm::vec2 screenPosition = entity->mTransform.position + entity->mVelocity * mInterpolation - mPosition;
    // Where the image is going to go and the size of the image.
    SDL_Rect dstRect = {
            static_cast<int>(screenPosition.x),
            static_cast<int>(screenPosition.y),
            static_cast<int>(mImages[entity->mImageRef].width * entity->mTransform.scale.x),
            static_cast<int>(mImages[entity->mImageRef].height * entity->mTransform.scale.y)
    };

    double screenRotation = entity->mTransform.rotation + entity->mAngularVelocity * mInterpolation;

    // srcrect is where to crop an image if it's within an atlas map.
    SDL_RenderCopyEx(mRenderer, mImages[entity->mImageRef].src, nullptr, &dstRect, screenRotation,
                     nullptr, SDL_FLIP_NONE);
}

void Renderer::renderItem(std::shared_ptr<HudText> &text)
{
    if (!text->isRenderable()) { return; }  // Text has been explicitly marked as non-renderable.
    if (!text->isRenderValid()) { changeText(text); }

    auto textIt = mTexts.find(text->getId());
    if (textIt == mTexts.end()) { throwError("Could not find Text."); }

    auto &textData = textIt->second;

    glm::ivec2 position = text->getPosition();
    char anchorPoint = text->getAnchorPoint();

    // Align the text compared to its anchor point.
    if ((anchorPoint & HudElement::Bottom) > 0)         { position.y += mRendererSize.y; }
    else if ((anchorPoint & HudElement::Center) > 0)    { position.y += mRendererSize.y / 2; }
    if ((anchorPoint & HudElement::Right) > 0)          { position.x += mRendererSize.x; }
    else if ((anchorPoint & HudElement::Middle) > 0)    { position.x += mRendererSize.x / 2; }

    SDL_Rect dstRect = {
            position.x,
            position.y,
            textData.width,
            textData.height
    };

    SDL_RenderCopyEx(mRenderer, textData.src, nullptr, &dstRect, 0.0, nullptr, SDL_FLIP_NONE);
}

void Renderer::renderItem(const std::shared_ptr<HudImage> &hudImage)
{
    if (!hudImage->isRenderable()) { return; }  // The image has explicitly been marked as non-renderable.
    auto imageIt = mImages.find(hudImage->getImageRef());
    if (imageIt == mImages.end()) { throwError("Could not find entities image src."); }

    auto &imageData = imageIt->second;

    glm::ivec2 position = hudImage->getPosition();
    char anchorPoint = hudImage->getAnchorPoint();

    // Align the text compared to its anchor point.
    if ((anchorPoint & HudElement::Bottom) > 0)         { position.y += mRendererSize.y; }
    else if ((anchorPoint & HudElement::Center) > 0)    { position.y += mRendererSize.y / 2; }
    if ((anchorPoint & HudElement::Right) > 0)          { position.x += mRendererSize.x; }
    else if ((anchorPoint & HudElement::Middle) > 0)    { position.x += mRendererSize.x / 2; }

    SDL_Rect dstRect = {
            position.x,
            position.y,
            static_cast<int>(static_cast<float>(imageData.width) * hudImage->getScale().x),
            static_cast<int>(static_cast<float>(imageData.height) * hudImage->getScale().y)
    };

    SDL_RenderCopyEx(mRenderer, imageData.src, nullptr, &dstRect, 0.0, nullptr, SDL_FLIP_NONE);
}

void Renderer::loadImage(const std::string &imageRef)
{
    if (imageRef.empty()) { return; }  // Item has no image ref.
    auto imageIt = mImages.find(imageRef);
    if (imageIt != mImages.end())  // Check to see if the image is already in the map.
    {
        imageIt->second.refCount++;
        return;
    }

    // Creat and add the image to map.
    SDL_Surface *loadedSurface = IMG_Load(imageRef.c_str());
    if (!loadedSurface)
    {
        throwError("Failed to find image: " + imageRef + ". Check location from executable");
    }
    // Convert surface to an optimised texture for renderer.
    SDL_Texture *optimisedTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);

    mImages[imageRef] = { optimisedTexture, loadedSurface->w, loadedSurface->h, 1 };
    // Free the surface that we just use to load the image.
    SDL_FreeSurface(loadedSurface);
}

void Renderer::loadText(std::shared_ptr<HudText> &text)
{
    auto id = text->getId();
    if (id != 0)  // Check to see if this text already exists (This should really never happen).
    {
        mTexts[id].refCount++;
        return;
    }

    // Create Text
    auto *font = text->getTextData();
    if (!font) { throwError("Font Could not be found or loaded properly."); }

    SDL_Color color { 255, 255, 255, 255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text->getText().c_str(), color);
    if (!textSurface) { throwError("Failed to render text."); }
    SDL_Texture *optimisedText = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (!optimisedText) { throwError("Could not optimise text."); }

    mTexts[mNextTextId] = imageData{ optimisedText, textSurface->w, textSurface->h, 1 };

    SDL_FreeSurface(textSurface);

    text->setId(mNextTextId);
    text->setRenderValid(true);
    mNextTextId++;
}

void Renderer::freeImage(const std::string &imageRef)
{
    if (imageRef.empty()) { return; }  // Item has not image ref.
    auto imageIt = mImages.find(imageRef);
    auto &imageData = imageIt->second;
    imageData.refCount--;
    if (imageData.refCount <= 0)  // Remove if there is no count to the object.
    {
        SDL_DestroyTexture(imageData.src);
        mImages.erase(imageIt);
    }
}

void Renderer::freeText(size_t id)
{
    if (id == 0) { return; }  // 0 explicitly doesn't exist with the map.
    auto textIt = mTexts.find(id);
    auto &textData = textIt->second;
    textData.refCount--;
    if (textData.refCount <= 0)  // Remove if there's nothing else pointing to this bit of text.
    {
        SDL_DestroyTexture(textData.src);
        mTexts.erase(textIt);
    }
}

void Renderer::changeText(std::shared_ptr<HudText> &text)
{
    auto textIt = mTexts.find(text->getId());
    auto &textData = textIt->second;
    // Destroy old texture.
    SDL_DestroyTexture(textData.src);
    textData.src = nullptr;

    TTF_Font *font = text->getTextData();
    if (!font) { throwError("Font Could not be found or loaded properly."); }

    SDL_Color color { 255, 255, 255, 255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text->getText().c_str(), color);
    if (!textSurface) { throwError("Failed to render text."); }
    SDL_Texture *optimisedText = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (!optimisedText) { throwError("Could not load optimised text."); }

    textData.src = optimisedText;

    textData.width = textSurface->w;
    textData.height = textSurface->h;


    SDL_FreeSurface(textSurface);


    text->setRenderValid(true);
}

void Renderer::update(const float &interpolation)
{
    mInterpolation = interpolation;
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    // Convert Entity to Shared pointer to get data.
    // Control blocks are thread safe.
    if (auto tgtEntity = mTargetEntity.lock())
    {
        // Put the entity in the center of the screen.
        mPosition = tgtEntity->mTransform.position - (glm::vec2(mRendererSize) / 2.f) + tgtEntity->mVelocity * mInterpolation;
    }
    else
    {
        mPosition = { 0.f, 0.f };
    }
}

void Renderer::setTarget(const std::weak_ptr<Entity> &entity)
{
    mTargetEntity = entity;
}

void Renderer::renderHitBox(const std::shared_ptr<Entity> &entity)
{
    quad::rect entityHitBox = entity->getHitBoxRect();
    entityHitBox.x -= mPosition.x;
    entityHitBox.y -= mPosition.y;
    SDL_Rect dstRect = {
            static_cast<int>(entityHitBox.x),
            static_cast<int>(entityHitBox.y),
            static_cast<int>(entityHitBox.w),
            static_cast<int>(entityHitBox.h)
    };
    SDL_SetRenderDrawColor(mRenderer, entity->mHitBoxColour.r, entity->mHitBoxColour.g, entity->mHitBoxColour.b, entity->mHitBoxColour.a);
    SDL_RenderDrawRect(mRenderer, &dstRect);
}

void Renderer::renderHitBox(const quad::rect &aabb)
{
    SDL_Rect dstRect = {
            static_cast<int>(aabb.x - mPosition.x),
            static_cast<int>(aabb.y - mPosition.y),
            static_cast<int>(aabb.w),
            static_cast<int>(aabb.h)
    };
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(mRenderer, &dstRect);
}
