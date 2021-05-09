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
class BarrierCollider;

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
           std::string imageRef = "");

    Entity(const glm::vec2 &position, const glm::vec2 &hitBoxSize, const glm::vec2 &hitBoxOffSet,
           const size_t &collisionLayer, std::string  imageRef = "assets/images/chad.bmp");

    /** Entity with image only. */
    Entity(const glm::vec2 &position, const glm::vec2 &imageSize, std::string imageRef = "assets/images/chad.bmp");

    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void onCollision(const std::shared_ptr<Entity> &other) = 0;

    quad::rect getHitBoxRect() const;
    glm::vec2 getHitBoxCenter() const;

protected:
    /**
     * Stops an entity from going out of bounds. Upon collision, it will
     * move the entity back to a valid place.
     * @param barrierCollider The bounding box that you want to test against.
     */
    void pushOffWall(const std::shared_ptr<BarrierCollider> &barrierCollider);

public:  // todo: convert this to protected fields.
    /** The position, rotation and size of the entity */
    transform mTransform;

    /** The velocity of the entity. Defined here so that the renderer can 'predict' where the entity will go */
    glm::vec2 mVelocity;

    /** The image displayed by the renderer. */
    const std::string mImageRef;

    /** Offset from the top-left most corner. */
    glm::vec2 mHitBoxOffset;

    /** How big the hit box is. */
    glm::vec2 mHitBoxSize;

    /** Used for debugging only. */
    glm::vec4 mHitBoxColour;

    /** What collision layer it is attached to. Used quad::layers to set this field. */
    const size_t mCollisionLayer;

    /** Flag for clean up an the end of a frame. */
    bool mIsDead;

    /** Toggle for the hit box */
    bool mIsCollidable;

    /** Toggle for the renderer to display an image */
    bool mIsRenderable;

    /** Rotational velocity */
    double mAngularVelocity;

    /** The layers in which this entity can collide with. */
    size_t mQueryLayers;
};


#endif //A2OOPGAME_ENTITY_H
