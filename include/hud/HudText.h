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
#include <SDL_ttf.h>

/**
 * Text that can appear on the HUD.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 04/05/2021]
 */
class HudText : public HudElement
{
public:
    explicit HudText(const glm::ivec2 &position, char anchorPoint=0);
    ~HudText() override;

    void update() override;

    void setText(const std::string &text);
    std::string getText() const;

    void setId(size_t newId);
    size_t getId() const;

    void setSize(int newSize);
    int getSize() const;
    TTF_Font *getTextData() const;

    bool isRenderValid() const;
    void setRenderValid(bool isValid);

protected:
    void createTextData();
    void freeTextData();

    TTF_Font *mTextData;
    std::string mFontPath;
    std::string mText;
    int mSize;
    glm::vec4 mColour;
    size_t mId;
    bool mIsRendererValid;
};


#endif //A2OOPGAME_HUDTEXT_H
