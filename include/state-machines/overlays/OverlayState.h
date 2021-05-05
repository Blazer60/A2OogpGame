/**
 * @file OverlayState.h
 * @brief A type of state that can overlay any other state.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 05/05/2021
 */


#ifndef A2OOPGAME_OVERLAYSTATE_H
#define A2OOPGAME_OVERLAYSTATE_H


#include "StateMachine.h"

/**
 * A type of state that can overlay any other state.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 05/05/2021]
 */
class OverlayState : public StateMachine
{
public:
    OverlayState(SDL_Renderer *renderer, const glm::ivec2 &windowSize,
                 std::weak_ptr<StateMachine> attachToState, char stateKey);

    void event(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

protected:
    std::weak_ptr<StateMachine> mAttachedToState;
};


#endif //A2OOPGAME_OVERLAYSTATE_H
