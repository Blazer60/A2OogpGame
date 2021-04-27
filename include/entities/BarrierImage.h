/**
 * @file Barrier.h
 * @brief [fill in this secton]
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
 * The Wall for the arena that entities are held in.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 19/04/2021]
 */
class BarrierImage : public Entity
{
public:
    explicit BarrierImage(const glm::vec2 &position=glm::vec2(0.f));

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;
};


#endif //A2OOPGAME_BARRIERIMAGE_H
