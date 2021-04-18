/**
 * @file StateMachineManager.h
 * @brief Handles all of the states loaded within the game and runs the core game loop.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 14/04/2021
 */


#ifndef A2OOPGAME_STATEMACHINEMANAGER_H
#define A2OOPGAME_STATEMACHINEMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <glm.hpp>
#include <unordered_map>
#include <memory>

class StateMachine;

namespace statesList
{
    enum states : char {
        MainMenu, InGame
    };
}

/**
 * Handles all of the states loaded within the game and runs the core game loop.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 14/04/2021]
 */
class StateMachineManager
{
    typedef std::unordered_map<char, std::shared_ptr<StateMachine>> stateMap;

public:
    explicit StateMachineManager(const glm::ivec2 &screenSize={ 640, 480 }, char skipToStateKey=statesList::MainMenu);
    ~StateMachineManager();

    void run();
    void changeState(char stateKey);

    bool mIsRunning;

protected:
    void runLogic();
    void runRenderer();

    void event();
    void update();
    void render();

    void addState(char stateKey);
    void removeState(char stateKey);

    stateMap mStates;
    std::shared_ptr<StateMachine> mCurrentState;

    glm::ivec2 mScreenSize;
    SDL_Window *mWindow;

    // Frame rate control
    const double mUpdateRatePerSecond;
    const double mUpdateDelta;
    const unsigned int mUpdateFrameSkip;
    double mNextUpdateTick;

    const double mRenderRatePerSecond;
    const double mRenderDelta;
    const unsigned int mRenderFrameSkip;
    double mNextRenderTick;
    double mInterpolation;
};


#endif //A2OOPGAME_STATEMACHINEMANAGER_H
