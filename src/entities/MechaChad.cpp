/**
 * @file MechaChad.cpp.cc
 * @brief The main boss that the player faces against.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#include "MechaChad.h"
#include "GameState.h"
#include "QuadTreeHelpers.h"

#include <iostream>

MechaChad::MechaChad(const glm::vec2 &position, GameState *attachToState, std::weak_ptr<Entity> targetEntity) :
    BaseEnemy(position, { 128, 128 }, attachToState, std::move(targetEntity)),
    timer(1),
    currentOption(ChargeTarget),
    mFireProjectileSound("../sfx/shurikenThrow.mp3"),
    mChangingStateSound("../tmp/BeepOne.mp3")
{
    mTransform.scale = glm::vec2(4.f);
    mHitBoxOffset = glm::vec2(64.f);
}

void MechaChad::update()
{
    timer--;
    switch (currentOption)
    {
        case ChargeTarget:
            chargeTarget();
            break;
        case ShootInCircle:
            shootInCircle();
            break;
        case ShootAtTarget:
        default:
            shootAtTarget();
            break;
    }

    if (timer <= 0)
    {
        changeOption();
    }

    float directionFacing = getTargetDirection().x;
    mTransform.scale.x = directionFacing > 0 ? -4.f : 4.f;
}

void MechaChad::shootAtTarget()
{
    shootTargetData.fireRateTimer++;
    if (shootTargetData.fireRateTimer >= shootTargetData.fireRate)
    {
        auto targetDirection = getTargetDirection();
        auto points = getUnitConePoints(shootTargetData.amountOfProjectiles, targetDirection, shootTargetData.coneSpread);
        for (const auto &point : points)
        {
            mGame->createEntity(std::make_shared<BaseProjectile>(mTransform.position + glm::vec2(128), point * glm::vec2(15), quad::layers::EnemyProjectile));
        }
        mFireProjectileSound.play();
        shootTargetData.fireRateTimer = 0;
    }
}

void MechaChad::shootInCircle()
{
    shootCircleData.fireRateTimer++;
    if (shootCircleData.fireRateTimer >= shootCircleData.fireRate)
    {
        shootCircleData.offSet += 47.12f;
        auto points = getUnitCirclePoints(shootCircleData.amountOfProjectiles, shootCircleData.offSet);
        for (const auto &point : points)
        {
            mGame->createEntity(std::make_shared<BaseProjectile>(mTransform.position + glm::vec2(128), point * glm::vec2(10), quad::layers::EnemyProjectile));
        }
        mFireProjectileSound.play();
        shootCircleData.fireRateTimer = 0;
    }
}

void MechaChad::changeOption()
{
    mVelocity = glm::vec2(0.f);
    currentOption = static_cast<char>((currentOption + 1) % 3);
    switch (currentOption)
    {
        case ChargeTarget:
            timer = chargeData.amountOfTime;
            shootCircleData.amountOfTime += 5;
            shootCircleData.amountOfProjectiles++;

            shootTargetData.amountOfProjectiles++;
            shootTargetData.fireRate = glm::max(5, shootTargetData.fireRate - 1);
            shootTargetData.coneSpread *= 1.1f;

            chargeData.speed = glm::min(25.f, chargeData.speed + 0.5f);
            break;
        case ShootInCircle:
            timer = shootCircleData.amountOfTime;
            break;
        default:
        case ShootAtTarget:
            timer = shootTargetData.amountOfTime;
    }
    mChangingStateSound.play();
}

void MechaChad::chargeTarget()
{
    auto targetDirection = getTargetDirection();
    mVelocity = targetDirection * chargeData.speed;
    mTransform.position += mVelocity;
}

void MechaChad::onCollision(const std::shared_ptr<Entity> &other)
{

}

glm::vec2 MechaChad::getTargetDirection()
{
    if (auto target = mTargetEntity.lock())
    {
        return glm::normalize(target->getHitBoxCenter() - getHitBoxCenter());
    }
    return glm::vec2(0.f);
}
