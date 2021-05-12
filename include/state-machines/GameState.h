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

#include <memory>
#include <vector>
#include <SDL_mixer.h>

class Music;
class HudImage;
class HudText;
class Player;
template<class dataType>
class QuadTree;
class LifeGauge;


/**
 * The game state that runs the actual game.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class GameState : public StateMachine
{
    typedef QuadTree<std::shared_ptr<Entity>> entityTree;
public:
    GameState(SDL_Renderer *renderer, const glm::ivec2 &windowSize);
    ~GameState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

    void createHudText(std::shared_ptr<HudText> text);
    void createEntity(const std::shared_ptr<Entity> &entity);
    void cleanEntities();
    void moveBufferedEntities();

protected:
    void collisionUpdateCheck();

    std::shared_ptr<Player> mPlayer;

    /** All entities. Enemies, Projectiles, etc. */
    std::vector<std::shared_ptr<Entity>> mEntities;

    /** Entities that have been spawned in this frame. */
    std::vector<std::shared_ptr<Entity>> mBufferedEntities;

    /** All of the text that appears on screen. */
    std::vector<std::shared_ptr<HudText>> mHudTexts;

    /** The three hearts seen at the bottom of the screen. */
    std::shared_ptr<LifeGauge> mLifeGauge;

    /** The quad tree and handles all of the collision checking */
    std::unique_ptr<entityTree> mQuadTree;

    std::unique_ptr<Music> mMusic;
};


#endif //A2OOPGAME_GAMESTATE_H
