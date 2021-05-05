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

#include "Entity.h"
#include "QuadTreeHelpers.h"

struct inputs;

/**
 * The main player class that the they can control.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class Player : public Entity
{
public:
    explicit Player(const glm::vec2 &position);

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

    int getLives() const;

    bool isInvulnerable() const;

protected:
    void makeInvulnerable(int frames);
    void makeVulnerable();

    float mSpeed;
    float mDashSpeedMultiplier;
    bool mCanDash;
    bool mInDash;
    int mDashLength;
    int mDashTimer;  // Count Down

    int mDashCoolDownFrames;
    int mDashCoolDownTimer;  // Counts up
    int mDashInvulnerableFrames;


    int mInvulnerableTimer;  // Counts Down
    bool mIsInvulnerable;
    glm::vec2 mDashDirection;

    int mLives;

    bool mGodMode;
};


#endif //A2OOPGAME_PLAYER_H
