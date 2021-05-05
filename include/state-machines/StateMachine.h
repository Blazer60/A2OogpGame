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
    explicit StateMachine(SDL_Renderer *renderer, const glm::ivec2 &windowSize, char stateKey);
    virtual ~StateMachine() = default;

    virtual void onPause() = 0;
    virtual void onAwake() = 0;

    virtual void event(StateMachineManager *smm) = 0;
    virtual void update(StateMachineManager *smm) = 0;
    virtual void render(StateMachineManager *smm, const float &interpolation) = 0;
    static void changeState(StateMachineManager *smm, char stateKey);

    char getStateKey() const;
    void flip();

protected:
    Renderer mRenderer;
    const char mStateKey;
};


#endif //A2OOPGAME_STATEMACHINE_H
