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


struct inputs
{
    bool up = false, down = false, left = false, right = false, space = false, leftClick = false, rightClick = false, esc = false;
    glm::vec2 mousePosition;
};

/**
 * The game state that runs the actual game.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 15/04/2021]
 */
class GameState : public StateMachine
{
    typedef QuadTree<std::shared_ptr<Entity>> entityTree;
public:
    explicit GameState(SDL_Window *window);
    ~GameState() override = default;

    void onPause() override;
    void onAwake() override;

    void event(StateMachineManager *smm) override;
    void update(StateMachineManager *smm) override;
    void render(StateMachineManager *smm, const float &interpolation) override;

    void createHudText(std::shared_ptr<HudText> text);

    void createEntity(const std::shared_ptr<Entity> &entity);
    void moveBufferedEntities();
    void cleanEntities();

protected:
    void collisionUpdateCheck();

    std::shared_ptr<Player> mPlayer;
    inputs mInputs;
    std::vector<std::shared_ptr<Entity>> mEntities;
    std::vector<std::shared_ptr<Entity>> mBufferedEntities;
    std::vector<std::shared_ptr<HudText>> mHudTexts;
//    std::vector<std::shared_ptr<HudImage>> mHudImages;
    std::shared_ptr<LifeGauge> mLifeGauge;
    std::unique_ptr<entityTree> mQuadTree;

    std::unique_ptr<Music> mMusic;
};


#endif //A2OOPGAME_GAMESTATE_H
