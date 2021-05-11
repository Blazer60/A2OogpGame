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
#include <SDL_ttf.h>
#include <SDL.h>

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

    void setRenderValid(bool isValid);
    bool isRenderValid() const;

    void setVisibility(bool visibility);
    bool isVisible() const;

    void setPosition(const glm::ivec2 &newPosition);

    void setColour(const SDL_Color &colour);
    SDL_Color getColour() const;

protected:
    void createTextData();
    void freeTextData();

    TTF_Font *mTextData;

    /** The path to ttf file */
    std::string mFontPath;

    std::string mText;

    /** The size of the text.  */
    int mSize;

    /** The colour of the text */
    SDL_Color mColour;

    /** The ID that is set by the renderer so that it can render the correct texture. */
    size_t mId;

    /** Lets the renderer know if anything has changed to this text. */
    bool mIsRendererValid;
};


#endif //A2OOPGAME_HUDTEXT_H
