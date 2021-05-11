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
#include "SoundFx.h"

/**
 * The main player class that the they can control.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class Player : public Entity
{
public:
    explicit Player(const glm::vec2 &position);
    ~Player() override = default;

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

    /**
     * @return Number of lives remaining.
     */
    int getLives() const;

    /**
     * @return True if it can't be damaged, False otherwise.
     */
    bool isInvulnerable() const;

protected:
    /**
     * Makes it so that the player can't take any damage.
     * @param frames How long would you like it to last.
     */
    void makeInvulnerable(int frames);

    /**
     * Makes it so that the player can be damaged.
     */
    void makeVulnerable();

    /** How fast the player can move */
    float mSpeed;

    /** The direction the player dodges.  */
    glm::vec2 mDashDirection;

    /** How much faster the player moves when dashing */
    float mDashSpeedMultiplier;

    /** Can the player dash?  */
    bool mCanDash;

    /** Is the player currently dashing  */
    bool mInDash;

    /** How long the player can dash for  */
    int mDashLength;

    /** How far into the dash the player currently is. (Counts down) */
    int mDashTimer;

    /** How long until the player can dash again. */
    int mDashCoolDownFrames;

    /** How far into the dash cool down the player currently is. (Counts up) */
    int mDashCoolDownTimer;

    /** How long the player is invulnerable for when dashing. */
    int mDashInvulnerableFrames;

    /** How far the player is into being invulnerable. (counts down) */
    int mInvulnerableTimer;

    bool mIsInvulnerable;
    int mLives;

    bool mGodMode;  // Used for debugging

    /** The sound the player makes when they take damage */
    SoundFx mHurtSound;
};


#endif //A2OOPGAME_PLAYER_H
