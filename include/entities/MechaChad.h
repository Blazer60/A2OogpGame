/**
 * @file MechaChad.h
 * @brief The main boss that the player faces against.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#ifndef A2OOPGAME_MECHACHAD_H
#define A2OOPGAME_MECHACHAD_H

#include "BaseEnemy.h"
#include "Entity.h"
#include "SoundFx.h"
#include "Ai.h"

#include <glm.hpp>
#include <memory>

struct chargeTargetData
{
    float speed = 10;
    int amountOfTime = 60;
};

struct shootAtTargetData
{
    int amountOfTime = 90;
    int fireRate = 30;
    int fireRateTimer = 0;
    int amountOfProjectiles = 3;
    float coneSpread = 45.f;
};

struct shootInCircleData
{
    int amountOfTime = 30;
    int fireRate = 5;
    int fireRateTimer = 0;
    int amountOfProjectiles = 4;
    float offSet = 0;
};

/**
 * The main boss that the player faces against.
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 19/04/2021]
 */
class MechaChad : public BaseEnemy
{
public:
    MechaChad(const glm::vec2 &position, GameState *attachToState, std::weak_ptr<Entity> targetEntity);

    void update() override;
    void onCollision(const std::shared_ptr<Entity> &other) override;

    void changeOption();
    void chargeTarget(float speed);
//    void shootAtTarget();
//    void shootInCircle();

    glm::vec2 getTargetDirection();
protected:
    Ai mBrain;
    chargeTargetData chargeData;
    shootAtTargetData shootTargetData;
    shootInCircleData shootCircleData;

    enum options : char { ChargeTarget, ShootAtTarget, ShootInCircle };
    char currentOption;
    unsigned int timer;
    SoundFx mFireProjectileSound;
    SoundFx mChangingStateSound;
};


#endif //A2OOPGAME_MECHACHAD_H
