/**
 * @file Entity.h
 * @brief The base entity class for every object that is rendered to the screen.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#ifndef A2OOPGAME_ENTITY_H
#define A2OOPGAME_ENTITY_H

#include <glm.hpp>
#include <string>
#include <memory>
#include <SDL.h>

namespace quad { struct rect; }


struct transform
{
    glm::vec2 position;
    double rotation;
    glm::vec2 scale;

    transform(const glm::vec2 &position, double rotation, const glm::vec2 &scale) :
        position(position), rotation(rotation), scale(scale)
    {}
};

/**
 * The base entity class for every object that is rendered to the screen.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class Entity
{
public:
    Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const size_t &collisionLayer,
           std::string imageRef = "../tmp/chad.bmp");

    Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const glm::vec2 &hitBoxOffSet,
           const size_t &collisionLayer, std::string  imageRef = "../tmp/chad.bmp");
    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void onCollision(const std::shared_ptr<Entity> &other) = 0;

    quad::rect getHitBoxRect() const;

public:  // todo: convert this to protected fields.
    transform mTransform;
    glm::vec2 mVelocity;
    const std::string mImageRef;
    glm::vec2 mHitBoxOffset;
    glm::vec2 mHitBoxSize;
    glm::vec4 mHitBoxColour;
    const size_t mCollisionLayer;
    bool mIsDead;
    double mAngularVelocity;
};


#endif //A2OOPGAME_ENTITY_H
