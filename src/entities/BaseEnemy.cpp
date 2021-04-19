/**
 * @file BaseEnemy.cpp.cc
 * @brief The base entity class for all enemies.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */

#include "GameState.h"
#include "BaseEnemy.h"
#include "Player.h"
#include <glm.hpp>
#include <gtc/constants.hpp>
#include <utility>

BaseEnemy::BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize, GameState *attachToState,
                     std::weak_ptr<Entity> targetEntity, const size_t &collisionLayer) :
        Entity(position, hitBoxSize, collisionLayer),
        mGame(attachToState),
        mTargetEntity(std::move(targetEntity))
{}

void BaseEnemy::update()
{
    glm::vec2 targetDirection(0);
    if (auto player = mTargetEntity.lock())
    {
        targetDirection = glm::normalize(player->mTransform.position - mTransform.position);
    }
    mVelocity = targetDirection * 5.f;
    mTransform.position += mVelocity;
    mGame->createEntity(std::make_shared<BaseProjectile>(mTransform.position, glm::vec2(10.f, 0.f), quad::layers::EnemyProjectile));
}

void BaseEnemy::onCollision(const std::shared_ptr<Entity> &other)
{

}

std::vector<glm::vec2> BaseEnemy::getUnitCirclePoints(unsigned int n, const float &offSet)
{
    std::vector<glm::vec2> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        float theta = static_cast<float>(i) / static_cast<float>(n) * glm::two_pi<float>() + offSet;
        float y = -glm::sin(theta);
        float x = glm::cos(theta);
        points.emplace_back(glm::vec2{ x, y });
    }
    return points;
}
