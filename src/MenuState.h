/**
 * @file MenuState.h
 * @brief [fill in this secton]
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#ifndef A2OOPGAME_MENUSTATE_H
#define A2OOPGAME_MENUSTATE_H

#include "StateMachine.h"

/**
 * [Description goes here.]
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class MenuState : public StateMachine
{
public:
    explicit MenuState(SDL_Window *window);
    ~MenuState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm) override;
};


#endif //A2OOPGAME_MENUSTATE_H
