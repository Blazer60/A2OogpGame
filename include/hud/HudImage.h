/**
 * @file HudImage.h
 * @brief An image that can be renderer to the screen
 * regardless of where the 'camera' position is.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#ifndef A2OOPGAME_HUDIMAGE_H
#define A2OOPGAME_HUDIMAGE_H


#include "HudElement.h"
#include <string>

/**
 * An image that can be renderer to the screen
 * regardless of where the 'camera' position is.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 04/05/2021]
 */
class HudImage : public HudElement
{
public:
    explicit HudImage(const glm::ivec2 &position, char anchorPoint=0, std::string imageRef="");
    ~HudImage() override = default;

    void update() override;

    std::string getImageRef();

protected:
    /** The image reference used by the renderer. */
    std::string mImageRef;
};


#endif //A2OOPGAME_HUDIMAGE_H
