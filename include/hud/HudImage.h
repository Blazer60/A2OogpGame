/**
 * @file HudImage.h
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#ifndef A2OOPGAME_HUDIMAGE_H
#define A2OOPGAME_HUDIMAGE_H


#include <string>
#include <unordered_map>
#include <glm.hpp>
#include "HudElement.h"

/**
 * [Description goes here.]
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
    std::string mImageRef;
};


#endif //A2OOPGAME_HUDIMAGE_H
