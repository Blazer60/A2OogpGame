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
    /** All states that the state machine manager is setup to handle. */
    enum states : char {
        MainMenu, InGame, Paused, DeathScreen
    };
}

namespace soundChannel
{
    enum channels : char {
        Master, Music, Sound
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

    /** Runs the game asynchronously. */
    [[deprecated("Use runSynchronous() instead.")]]
    void run();

    /** Runs the game synchronously */
    void runSynchronous();

    void changeState(char stateKey);

    void setVolume(char channel, float percentage, bool isAdditive=false);
    float getVolume(char channel) const;

    bool mIsRunning;

protected:
    /** Asynchronous logic loop */
    void runLogic();

    /** Asynchronous render loop */
    void runRenderer();

    void event();
    void update();
    void render();

    void addState(char &stateKey);
    void removeState(char stateKey);

    stateMap mStates;
    std::shared_ptr<StateMachine> mCurrentState;

    glm::ivec2 mScreenSize;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    // Frame rate control
    const double mUpdateRatePerSecond;
    const double mUpdateDelta;
    const unsigned int mUpdateFrameSkip;  // Forces rendering after a set amount of ticks.
    double mNextUpdateTick;

    // Render rate control (unused)
    const double mRenderRatePerSecond;
    const double mRenderDelta;
    const unsigned int mRenderFrameSkip;
    double mNextRenderTick;

    /**
     * Used to predict how far into the update function
     * we are rendering. This allows for smooth movement
     * regardless of tick rate.
     * 0 - start of update tick.
     * 1 - start of next update tick.
     */
    double mInterpolation;

    // Music & Sound control
    float mMasterVolumePercentage;
    float mMusicVolumePercentage;
    float mSoundVolumePercentage;
};


#endif //A2OOPGAME_STATEMACHINEMANAGER_H
