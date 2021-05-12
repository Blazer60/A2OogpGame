/**
 * @file MenuState.h
 * @brief The first state that is loaded when the game is created.
 * Allows the user to play the game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#ifndef A2OOPGAME_MENUSTATE_H
#define A2OOPGAME_MENUSTATE_H

#include "StateMachine.h"
#include "Music.h"

#include <memory>
#include <vector>
#include <SDL_mixer.h>

/**
 * The first state that is loaded when the game is created.
 * Allows the user to play the game.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class MenuState : public StateMachine
{
public:
    MenuState(SDL_Renderer *renderer, const glm::ivec2 &windowSize, float volumePercentage);
    ~MenuState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

    void updateVolumeText(StateMachineManager *smm);

protected:
    void addText(const std::string& text);

    std::shared_ptr<HudText> mTitle;
    int mTitleFlashTimer;

    /** How often the title should flash. */
    int mTitleFlashRate;

    std::shared_ptr<HudText> mVolumeText;

    /** The rest of the text that is static */
    std::vector<std::shared_ptr<HudText>> mTexts;

    /** How far down the next piece of text should be. */
    int mTextYAdvance;

    /** The Y pos of the next piece of text */
    int mTextYPos;

    /** The size of all of the text in mTexts. */
    int mSize;

    Music mMusic;
};


#endif //A2OOPGAME_MENUSTATE_H
