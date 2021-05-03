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
public:
    explicit Renderer(SDL_Window *window);
    ~Renderer();

    void update(const float &interpolation);
    void renderItem(const std::shared_ptr<Entity> &entity);
    void renderHitBox(const std::shared_ptr<Entity> &entity);
    void renderHitBox(const quad::rect &aabb);
    void flip();
    void loadImage(const std::string &imageRef);
    void freeImage(const std::string &imageRef);
    void setTarget(const std::weak_ptr<Entity> &entity);

protected:
    glm::ivec2 mRendererSize;
    SDL_Renderer *mRenderer;
    imageMap mImages;
    float mInterpolation;
    std::weak_ptr<Entity> mTargetEntity;
    glm::vec2 mPosition;
};


#endif //A2OOPGAME_RENDERER_H
