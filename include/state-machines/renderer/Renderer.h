/**
 * @file Renderer.h
 * @brief Handles rendering entities to the screen. Each state machine contains their own renderer.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#ifndef A2OOPGAME_RENDERER_H
#define A2OOPGAME_RENDERER_H

#include <SDL.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <glm.hpp>
#include <QuadTreeHelpers.h>

class Entity;
class HudText;
class HudImage;

struct imageData
{
    SDL_Texture *src;
    int width, height;
    size_t refCount;
};

/**
 * Handles rendering entities to the screen. Each state machine contains their own renderer.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class Renderer
{
    typedef std::unordered_map<std::string, imageData> imageMap;
    typedef std::unordered_map<size_t, imageData> textMap;
public:
    Renderer(SDL_Renderer *renderer, const glm::ivec2 &windowSize);
    ~Renderer();

    void update(const float &interpolation);
    void renderItem(const std::shared_ptr<Entity> &entity);
    void renderItem(std::shared_ptr<HudText> &text);
    void renderItem(const std::shared_ptr<HudImage> &hudImage);
    void renderHitBox(const std::shared_ptr<Entity> &entity);
    void renderHitBox(const quad::rect &aabb);
    void flip();
    void loadImage(const std::string &imageRef);
    void freeImage(const std::string &imageRef);
    void setTarget(const std::weak_ptr<Entity> &entity);
    void loadText(std::shared_ptr<HudText> &text);
    void changeText(std::shared_ptr<HudText> &text);
    void freeText(size_t id);

protected:
    glm::ivec2 mRendererSize;
    SDL_Renderer *mRenderer;
    imageMap mImages;
    textMap mTexts;
    size_t mNextTextId;
    float mInterpolation;
    std::weak_ptr<Entity> mTargetEntity;
    glm::vec2 mPosition;
};


#endif //A2OOPGAME_RENDERER_H
