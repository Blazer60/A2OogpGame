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

Renderer::Renderer(SDL_Window *window) :
        mRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
        mInterpolation(0.f)
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

    // Where the image is going to go and the size of the image.
    SDL_Rect dstRect = {
            static_cast<int>(entity->mTransform.position.x + entity->mVelocity.x * mInterpolation),
            static_cast<int>(entity->mTransform.position.y + entity->mVelocity.y * mInterpolation),
            mImages[entity->mImageRef].width, mImages[entity->mImageRef].height
    };

    // srcrect is where to crop an image if it's within an atlas map.
    SDL_RenderCopy(mRenderer, mImages[entity->mImageRef].src,
                   nullptr, dstRect);
}

void Renderer::loadImage(const std::string &imageRef)
{
    SDL_Surface *loadedSurface = SDL_LoadBMP(imageRef.c_str());
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
