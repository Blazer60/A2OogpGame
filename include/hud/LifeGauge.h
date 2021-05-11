/**
 * @file LifeGauge.h
 * @brief The life gauge that shows how many lives that player has.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#ifndef A2OOPGAME_LIFEGAUGE_H
#define A2OOPGAME_LIFEGAUGE_H

#include "HudElement.h"
#include "HudImage.h"

#include <string>
#include <array>

class Player;

/**
 * The life gauge that shows how many lives that player has.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 04/05/2021]
 */
class LifeGauge : public HudImage
{
public:
    explicit LifeGauge(const glm::ivec2 &position, char anchorPoint);
    ~LifeGauge() override = default;

    void setImageRef(int refNumber);

    int getCurrentRefNumber() const;

protected:
    std::array<std::string, 4> mLifeImages;
    int mCurrentRefNumber;
};


#endif //A2OOPGAME_LIFEGAUGE_H
