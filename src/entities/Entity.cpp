/**
 * @file Entity.cpp.cc
 * @brief The base entity class for every object that is rendered to the screen.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#include "Entity.h"

#include <utility>

Entity::Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, std::string imageRef) :
    mTransform(position, 0.f, glm::vec2(1.f, 1.f)),
    mHitBoxSize(hitBoxSize),
    mImageRef(std::move(imageRef))
{}
