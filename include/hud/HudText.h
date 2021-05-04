/**
 * @file HudText.h
 * @brief Text that can appear on the HUD.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#ifndef A2OOPGAME_HUDTEXT_H
#define A2OOPGAME_HUDTEXT_H

#include "HudElement.h"

#include <string>
#include <glm.hpp>

/**
 * Text that can appear on the HUD.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 04/05/2021]
 */
class HudText : public HudElement
{
public:
    explicit HudText(const glm::ivec2 &position, char anchorPoint=0);
    ~HudText() override = default;

    void setText(const std::string &text);

protected:
    std::string mFontPath;
    std::string mText;
    int mSize;
    glm::vec4 mColour;
    size_t *mId;
};


#endif //A2OOPGAME_HUDTEXT_H
