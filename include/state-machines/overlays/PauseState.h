/**
 * @file PauseState.h
 * @brief A state that can attach itself to another state allowing it to be paused.
 * Used when you still want the underlying state to be rendered.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 05/05/2021
 */


#ifndef A2OOPGAME_PAUSESTATE_H
#define A2OOPGAME_PAUSESTATE_H

#include "StateMachine.h"
#include "OverlayState.h"

/**
 * A state that can attach itself to another state allowing it to be paused.
 * Used when you still want the underlying state to be rendered.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 05/05/2021]
 */
class PauseState : public OverlayState
{
public:
    PauseState(SDL_Renderer *renderer, const glm::ivec2 &windowSize, std::weak_ptr<StateMachine> attachedTo,
               float volumePercentage);

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

protected:
    void updateVolumeText(StateMachineManager *smm);

    std::shared_ptr<HudImage> mPauseIcon;
    std::shared_ptr<HudText> mPauseText;
    std::shared_ptr<HudText> mVolumeText;
};


#endif //A2OOPGAME_PAUSESTATE_H
