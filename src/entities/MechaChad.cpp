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
    timer(0)
{
    mTransform.scale = glm::vec2(4.f);
    mHitBoxOffset = glm::vec2(64.f);
}

void MechaChad::update()
{
    timer++;
    if (timer > 120)
    {
        timer = 0;
        std::vector<glm::vec2> points = getUnitCirclePoints(64);
        for (const auto &point : points)
        {
            mGame->createEntity(std::make_shared<BaseProjectile>(mTransform.position + glm::vec2(128), point * glm::vec2(10), quad::layers::EnemyProjectile));
        }
    }

}

void MechaChad::onCollision(const std::shared_ptr<Entity> &other)
{

}
