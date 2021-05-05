/**
 * @file DeathState.h
 * @brief The death screen that comes up after the
 * player has died within the game.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 05/05/2021
 */


#ifndef A2OOPGAME_DEATHSTATE_H
#define A2OOPGAME_DEATHSTATE_H

#include "OverlayState.h"
#include <memory>

/**
 * The death screen that comes up after the
 * player has died within the game.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 05/05/2021]
 */
class DeathState : public OverlayState
{
public:
    DeathState(SDL_Renderer *renderer, const glm::ivec2 &widowSize, std::weak_ptr<StateMachine> attachedTo);
    ~DeathState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

    std::shared_ptr<HudText> mTitle;
    std::shared_ptr<HudText> mScoreCard;
    std::shared_ptr<HudText> mTip;
};


#endif //A2OOPGAME_DEATHSTATE_H
