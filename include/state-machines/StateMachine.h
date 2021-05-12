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

#include "Renderer.h"

class StateMachineManager;

/**
 * The base class used for State Machines.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class StateMachine
{
public:
    explicit StateMachine(SDL_Renderer *renderer, const glm::ivec2 &windowSize, char stateKey);
    virtual ~StateMachine() = default;

    /** Called when the state is exited. */
    virtual void onPause() = 0;

    /** Called when the state is reactivated. Not when it is first initialised. */
    virtual void onAwake() = 0;

    /** Called before update. Typically used for SDL Input */
    virtual void event(StateMachineManager *smm) = 0;

    /** Called every update tick. (30 ticks per second) */
    virtual void update(StateMachineManager *smm) = 0;

    /** Called when there is excess time from updating. (Variable call rate) */
    virtual void render(StateMachineManager *smm, const float &interpolation) = 0;

    /** Allows the state to switch to another state. */
    static void changeState(StateMachineManager *smm, char stateKey);

    char getStateKey() const;

    /** Pushes anything in the render buffer to the screen. */
    void flip();

protected:
    /** The renderer attached to this state. */
    Renderer mRenderer;

    /** The Id of this state. */
    const char mStateKey;
};


#endif //A2OOPGAME_STATEMACHINE_H
