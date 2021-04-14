/**
 * @file Renderer.cpp.cc
 * @brief Handles rendering entities to the screen. Each state machine contains their own renderer.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#include "Renderer.h"

Renderer::Renderer(SDL_Window *window) :
    mRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{}
