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

MechaChad::MechaChad(const glm::vec2 &position, GameState *attachToState, std::weak_ptr<Entity> targetEntity) :
    BaseEnemy(position, { 128, 128 }, attachToState, std::move(targetEntity)),
    timer(1),
    currentOption(ChargeTarget)
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
}

void MechaChad::shootAtTarget()
{
    shootTargetData.fireRateTimer++;
    if (shootTargetData.fireRateTimer >= shootTargetData.fireRate)
    {
        auto targetDirection = getTargetDirection();
        auto points = getUnitConePoints(9, targetDirection, 45.f);
        for (const auto &point : points)
        {
            mGame->createEntity(std::make_shared<BaseProjectile>(mTransform.position + glm::vec2(128), point * glm::vec2(10), quad::layers::EnemyProjectile));
        }
        shootTargetData.fireRateTimer = 0;
    }
}

void MechaChad::shootInCircle()
{
    shootCircleData.fireRateTimer++;
    if (shootCircleData.fireRateTimer >= shootCircleData.fireRate)
    {
        shootCircleData.offSet += 10;
        auto points = getUnitCirclePoints(8, shootCircleData.offSet);
        for (const auto &point : points)
        {
            mGame->createEntity(std::make_shared<BaseProjectile>(mTransform.position + glm::vec2(128), point * glm::vec2(10), quad::layers::EnemyProjectile));
        }
        shootCircleData.fireRateTimer = 0;
    }
}

void MechaChad::changeOption()
{
    mVelocity = glm::vec2(0.f);
    currentOption = (currentOption + 1) % 3;
    std::cout << "switching state" << std::endl;
    switch (currentOption)
    {
        case ChargeTarget:
            timer = chargeData.amountOfTime;
            break;
        case ShootInCircle:
            timer = shootCircleData.amountOfTime;
            break;
        default:
        case ShootAtTarget:
            timer = shootTargetData.amountOfTime;
    }
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
