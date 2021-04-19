/**
 * @file MechaChad.h
 * @brief The main boss that the player faces against.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#ifndef A2OOPGAME_MECHACHAD_H
#define A2OOPGAME_MECHACHAD_H

#include "BaseEnemy.h"
#include "Entity.h"


#include <glm.hpp>
#include <memory>

/**
 * The main boss that the player faces against.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 19/04/2021]
 */
class MechaChad : public BaseEnemy
{
public:
    MechaChad(const glm::vec2 &position, GameState *attachToState, std::weak_ptr<Entity> targetEntity);

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

protected:
    unsigned int timer;
};


#endif //A2OOPGAME_MECHACHAD_H
