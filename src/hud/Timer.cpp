/**
 * @file Timer.cpp.cc
 * @brief A timer that keeps track of how long the player has been alive for.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#include "Timer.h"

Timer::Timer(const glm::ivec2 &position, char anchorPoint) : HudText(position, anchorPoint),
    mTime(0), mSeconds(0), mMinutes(0), mMs(0), mLeadingZeroLength(2)
{}

void Timer::update()
{
    mTime++;
    calculateTime();

    std::string minutes = std::to_string(mMinutes);
    minutes = std::string(mLeadingZeroLength - minutes.length(), '0') + minutes;

    std::string seconds = std::to_string(mSeconds);
    seconds = std::string(mLeadingZeroLength - seconds.length(), '0') + seconds;

    std::string milliSeconds = std::to_string(mMs);
    milliSeconds = std::string(mLeadingZeroLength - milliSeconds.length(), '0') + milliSeconds;
    setText(minutes + ":" + seconds + ":" + milliSeconds);
}

void Timer::calculateTime()
{
    // The game runs at a fixed rate of 30 frames a second.
    size_t framesLeft = mTime;

    mMinutes = framesLeft / 1800;  // 1800 is the number of frames that pass in a minute.
    framesLeft -= 1800 * mMinutes;

    mSeconds = framesLeft / 30;  // 30 is the number of frames that pass in a second.
    framesLeft -= 30 * mSeconds;

    mMs = 3 * framesLeft;
}
