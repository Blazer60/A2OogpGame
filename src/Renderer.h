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

struct imageData
{
    SDL_Texture *src;
    int width, height;
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

    void update();
    void renderItem(const std::string &imageRef);
    void flip();
    void loadImage(const std::string &imageRef);
    void freeImage(const std::string &imageRef);

protected:
    SDL_Renderer *mRenderer;
    imageMap mImages;
};


#endif //A2OOPGAME_RENDERER_H
