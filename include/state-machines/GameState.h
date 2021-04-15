/**
 * @file GameState.h
 * @brief The game state that runs the actual game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */


#ifndef A2OOPGAME_GAMESTATE_H
#define A2OOPGAME_GAMESTATE_H

#include "StateMachine.h"
#include "Player.h"

#include <memory>
#include <vector>

/**
 * The game state that runs the actual game.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class GameState : public StateMachine
{
public:
    explicit GameState(SDL_Window *window);
    ~GameState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm, const float &deltaTime) override;
    void render(StateMachineManager *smm) override;

protected:
    std::shared_ptr<Player> player;
    //std::vector<std::shared_ptr<Entity>> entities;
};


#endif //A2OOPGAME_GAMESTATE_H
