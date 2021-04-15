/**
 * @file Player.h
 * @brief The main player class that the they can control.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#ifndef A2OOPGAME_PLAYER_H
#define A2OOPGAME_PLAYER_H

#include <Entity.h>

/**
 * The main player class that the they can control.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class Player : public Entity
{
public:
    Player(const glm::vec2 &position, const glm::vec2 &hitBoxSize);

    void update(float deltaTime) override;
    void onCollision(const Entity &other) override;

protected:
    float mSpeed;
};


#endif //A2OOPGAME_PLAYER_H
