/**
 * @file Barrier.h
 * @brief The Wall for the arena that entities are held in. This is only the image part.
 * See wall collider for actual bounding boxes
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#ifndef A2OOPGAME_BARRIERIMAGE_H
#define A2OOPGAME_BARRIERIMAGE_H

#include "Entity.h"

#include <glm.hpp>

/**
 * The Wall for the arena that entities are held in. This is only the image part.
 * See wall collider for actual bounding boxes
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 19/04/2021]
 */
class BarrierImage : public Entity
{
public:
    explicit BarrierImage(const glm::vec2 &position=glm::vec2(0.f));
    ~BarrierImage() override = default;

    /** Doesn't do anything. */
    void update() override;

    /** Doesn't do anything/ */
    void onCollision(const std::shared_ptr<Entity> &other) override;
};


#endif //A2OOPGAME_BARRIERIMAGE_H
