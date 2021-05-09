/**
 * @file MechaChad.cpp.cc
 * @brief The main boss that the player faces against.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#include "MechaChad.h"
#include "ChargeNode.h"
#include "ShootInCircleNode.h"
#include "ShootAtTargetNode.h"
#include "BaseEnemy.h"
#include "BaseProjectile.h"

MechaChad::MechaChad(const glm::vec2 &position, GameState *attachToState, std::weak_ptr<Entity> targetEntity) :
    BaseEnemy(position, { 128, 128 }, attachToState, std::move(targetEntity)),
    mBrain(this)
{
    // Set up for the brain to run.
    mBrain.createNode(Move, std::make_unique<ChargeNode>(this, "assets/sfx/SpeedUp.mp3"));
    mBrain.createNode(BasicDirectedShot, std::make_unique<ShootAtTargetNode>(this));
    mBrain.createNode(BasicCircleShot, std::make_unique<ShootInCircleNode>(this));

    auto bounceNode = std::make_unique<ShootInCircleNode>(this, "assets/sfx/PowerSurge.mp3", "assets/sfx/Arrow.mp3");
    bounceNode->setProjectileType(projectiles::Ricochet);
    bounceNode->setAmountOfProjectiles(4);
    bounceNode->setActionRateMultiplier(1.f);
    mBrain.createNode(BounceCircleShot, std::move(bounceNode));

    auto momentumNode = std::make_unique<ShootAtTargetNode>(this, "assets/sfx/PowerUp.mp3", "assets/sfx/Laser.mp3");
    momentumNode->setProjectileType(projectiles::Momentum);
    momentumNode->setAmountOfProjectiles(3);
    momentumNode->setProjectileCountIncrease(2);
    momentumNode->setWarmUpTime(60);
    momentumNode->setMaxTime(120);
    momentumNode->setConeSpread(1.f);
    momentumNode->setConeSpreadMultiplier(2.f);
    momentumNode->setActionRate(5.f);
    momentumNode->setMinimumActionRate(1.f);
    momentumNode->setProjectileVelocity(glm::vec2(1.5f));  // In this case, it's acceleration.
    mBrain.createNode(MomentumShot, std::move(momentumNode));

    auto hexNode = std::make_unique<ShootInCircleNode>(this, "assets/sfx/MorphSound.mp3", "assets/sfx/AirBlast.mp3");
    hexNode->setProjectileType(projectiles::Hexed);
    hexNode->setAmountOfProjectiles(1);
    hexNode->setProjectileCountIncrease(1);
    hexNode->setMaxTime(30.f);
    hexNode->setActionRate(25.f);
    hexNode->setActionRateMultiplier(1.f);
    mBrain.createNode(HexedShot, std::move(hexNode));

    // The order in which things are executed.
    mBrain.setConnections({
        Move,
        BasicDirectedShot,
        BasicCircleShot,
        Move,
        MomentumShot,
        Move,
        BounceCircleShot,
        BasicDirectedShot,
        Move,
        HexedShot
    });
    mTransform.scale = glm::vec2(4.f);
    mHitBoxOffset = glm::vec2(64.f);

//    mBrain.advanceToStage(50);
}

void MechaChad::update()
{
    mBrain.update();
    float directionFacing = getTargetDirection().x;
    mTransform.scale.x = directionFacing > 0 ? -4.f : 4.f;
}

void MechaChad::onCollision(const std::shared_ptr<Entity> &other)
{

}

