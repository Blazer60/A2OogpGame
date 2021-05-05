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
    MenuState(SDL_Renderer *renderer, const glm::ivec2 &windowSize);
    ~MenuState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

    std::shared_ptr<HudText> mTitle;
};


#endif //A2OOPGAME_MENUSTATE_H
