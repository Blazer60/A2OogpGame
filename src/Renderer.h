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

/**
 * Handles rendering entities to the screen. Each state machine contains their own renderer.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class Renderer
{
    // Trialling how to use SDL objects with smart pointers, may or may not work.
    typedef std::unordered_map<std::string, std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>> imageMap;
public:
    explicit Renderer(SDL_Window *window);

    //void update();
    //void renderItem(ENTITY);
    void flip();
    void loadImage(const std::string &imageRef);
    void freeImage(const std::string &imageRef);

protected:
    SDL_Renderer *mRenderer;
    imageMap mImages;
};


#endif //A2OOPGAME_RENDERER_H
