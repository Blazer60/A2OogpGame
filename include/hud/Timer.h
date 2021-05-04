/**
 * @file Timer.h
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#ifndef A2OOPGAME_TIMER_H
#define A2OOPGAME_TIMER_H

#include <HudText.h>

/**
 * A timer that keeps track of how long the player has been alive for.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 04/05/2021]
 */
class Timer : public HudText
{
public:
    explicit Timer(const glm::ivec2 &position, char anchorPoint=0);
    ~Timer() override = default;

    void update() override;

protected:
    void calculateTime();

    size_t mTime;  // in frames
    size_t mMs;
    size_t mSeconds;
    size_t mMinutes;
    int mLeadingZeroLength;
};


#endif //A2OOPGAME_TIMER_H
