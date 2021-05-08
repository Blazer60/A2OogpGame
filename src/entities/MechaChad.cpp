/**
 * @file MechaChad.cpp.cc
 * @brief The main boss that the player faces against.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#include "MechaChad.h"
//#include "GameState.h"

MechaChad::MechaChad(const glm::vec2 &position, GameState *attachToState, std::weak_ptr<Entity> targetEntity) :
    BaseEnemy(position, { 128, 128 }, attachToState, std::move(targetEntity)),
    mBrain(this)
{
    mTransform.scale = glm::vec2(4.f);
    mHitBoxOffset = glm::vec2(64.f);
}

void MechaChad::update()
{
    mBrain.update();
    float directionFacing = getTargetDirection().x;
    mTransform.scale.x = directionFacing > 0 ? -4.f : 4.f;
}

void MechaChad::chargeTarget(float speed)
{
    auto targetDirection = getTargetDirection();
    mVelocity = targetDirection * speed;
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
