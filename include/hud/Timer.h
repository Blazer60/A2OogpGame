/**
 * @file Timer.h
 * @brief A timer that keeps track of how long the player has been alive for.
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

    /** The time they have survived for in frames. */
    size_t mTime;

    /** The millisecond sub division of time. */
    size_t mMs;

    /** The second sub division of time. */
    size_t mSeconds;

    /** The minute sub division of time. */
    size_t mMinutes;

    /** The amount of leading zero's each section should have. */
    int mLeadingZeroLength;
};


#endif //A2OOPGAME_TIMER_H
