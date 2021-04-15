/**
 * @file StateMachine.h
 * @brief The base class used for State Machines.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#ifndef A2OOPGAME_STATEMACHINE_H
#define A2OOPGAME_STATEMACHINE_H

#include "renderer/Renderer.h"

class StateMachineManager;

/**
 * The base class used for State Machines.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class StateMachine
{
public:
    explicit StateMachine(SDL_Window *window);
    virtual ~StateMachine() = default;

    virtual void onPause() = 0;
    virtual void onAwake() = 0;

    virtual void event(StateMachineManager *smm) = 0;
    virtual void update(StateMachineManager *smm, const float &deltaTime) = 0;
    virtual void render(StateMachineManager *smm) = 0;
    static void changeState(StateMachineManager *smm, char stateKey);

protected:
    Renderer mRenderer;
};


#endif //A2OOPGAME_STATEMACHINE_H
