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

#include <iostream>
#include <SDL_image.h>
#include <QuadTreeHelpers.h>

Renderer::Renderer(SDL_Window *window) :
        mRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
        mInterpolation(0.f), mPosition(0), mRendererSize(windowSizeToVec2(window))
{}

void Renderer::flip()
{
    SDL_RenderPresent(mRenderer);
}

void Renderer::renderItem(const std::shared_ptr<Entity> &entity)
{
    auto imageIt = mImages.find(entity->mImageRef);
    if (imageIt == mImages.end())
    {
        loadImage(entity->mImageRef);
    }

    glm::vec2 screenPosition = entity->mTransform.position + entity->mVelocity * mInterpolation - mPosition;
    // Where the image is going to go and the size of the image.
    SDL_Rect dstRect = {
            static_cast<int>(screenPosition.x),
            static_cast<int>(screenPosition.y),
            static_cast<int>(mImages[entity->mImageRef].width * entity->mTransform.scale.x),
            static_cast<int>(mImages[entity->mImageRef].height * entity->mTransform.scale.y)
    };

    // srcrect is where to crop an image if it's within an atlas map.
    SDL_RenderCopy(mRenderer, mImages[entity->mImageRef].src,
                   nullptr, dstRect);
}

void Renderer::loadImage(const std::string &imageRef)
{
    SDL_Surface *loadedSurface = IMG_Load(imageRef.c_str());
    if (!loadedSurface)
    {
        throwError("Failed to find image: " + imageRef + ". Check location from executable");
    }
    // Convert surface to an optimised texture for renderer.
    SDL_Texture *optimisedTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);

    mImages[imageRef] = { optimisedTexture, loadedSurface->w, loadedSurface->h };
    // Free the surface that we just use to load the image.
    SDL_FreeSurface(loadedSurface);
}

void Renderer::freeImage(const std::string &imageRef)
{
    SDL_DestroyTexture(mImages[imageRef].src);
    mImages.erase(imageRef);
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

Renderer::~Renderer()
{
    for (auto &item : mImages)
    {
        SDL_DestroyTexture(item.second.src);
    }
    // We can't erase in place while iterating.
    mImages.clear();
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

void Renderer::renderHitBox(const glm::vec4 &rect)
{
    SDL_Rect dstRect = {
            static_cast<int>(rect.x - mPosition.x),
            static_cast<int>(rect.y - mPosition.y),
            static_cast<int>(rect.z),
            static_cast<int>(rect.w)
    };
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(mRenderer, &dstRect);
}
